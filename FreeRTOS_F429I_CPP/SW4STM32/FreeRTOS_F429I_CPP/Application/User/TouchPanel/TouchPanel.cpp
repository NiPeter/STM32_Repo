/*
 * TouchPanel.cpp
 *
 *  Created on: 16 sie 2017
 *      Author: Peter
 */

#include "TouchPanel.hpp"



/**
 *
 * @param hadc
 * @param hgpio
 * @param upL
 * @param upR
 * @param btL
 * @param btR
 */
/********************************************************/
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t upR, uint16_t upL, uint16_t loR, uint16_t loL,osSemaphoreId semaphore):
				hADC(hadc),UpperLeft(hgpio,upL),UpperRight(hgpio,upR),LowerLeft(hgpio,loL),LowerRight(hgpio,loR),Semaphore(semaphore){
	FilterInit();
};
/********************************************************/



/**
 *
 * @param hadc
 * @param upL
 * @param upR
 * @param btL
 * @param btR
 */
/********************************************************/
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, Pin upR, Pin upL, Pin loR, Pin loL,osSemaphoreId semaphore):
				hADC(hadc),UpperLeft(upL),UpperRight(upR),LowerLeft(loL),LowerRight(loR),Semaphore(semaphore){
	FilterInit();
};
/********************************************************/






/**
 *
 * @return
 */
/********************************************************/
ADC_TypeDef* TouchPanel::GetADCInstance(void){
	return this->hADC->Instance;
}
/********************************************************/



/**
 *
 */
/********************************************************/
void TouchPanel::Process(void){

	CheckTouch();
	if( !Touched ){
		X=0;
		Y=0;
		return;
	}
	CheckX();
	CheckY();
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
bool TouchPanel::CheckTouch( void ){
	SetHighPolar();
	Measure();
//	FilterTouch->Reset();

	osSemaphoreWait(Semaphore,osWaitForever);

//	for(uint8_t i=0; i<BufferSize-1; i++){
//		FilterTouch->Filter( Data[i] );
//	}
//	float value = FilterTouch->Filter( Data[BufferSize-1] );

	float value = Average(Data,BufferSize);

	if(value > Treshold) Touched = true;
		else Touched = false;

	return Touched;
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float TouchPanel::CheckX(void){

	SetXPolar();
	Measure();
	FilterX->Reset();
	osSemaphoreWait(Semaphore,osWaitForever);

	for(uint8_t i=0; i<BufferSize-1; i++){
		FilterX->Filter( Data[i] );
	}
	float value = FilterX->Filter( Data[BufferSize-1] );

	X = value;
//	osSemaphoreWait(Semaphore,osWaitForever);
//	float value = Average(Data,BufferSize);
//
//	value = FilterX->Filter(value);
//
//	if(value != 0) X = value;


	return X;

}
/********************************************************/




/**
 *
 * @return
 */
/********************************************************/
float TouchPanel::CheckY(void){

	SetYPolar();
	Measure();
	FilterY->Reset();
	osSemaphoreWait(Semaphore,osWaitForever);

	for(uint8_t i=0; i<BufferSize-1; i++){
		FilterY->Filter( Data[i] );
	}
	float value = FilterY->Filter( Data[BufferSize-1] );

	Y = value;
//	osSemaphoreWait(Semaphore,osWaitForever);
//	float value = Average(Data,BufferSize);
//
//	value = FilterY->Filter(value);
//
//	if(value != 0) Y = value;

	return Y;

}
/********************************************************/


/**
 *
 */
/********************************************************/
void TouchPanel::Measure(void){
	HAL_ADC_Start_DMA(hADC,(uint32_t*)Data,BufferSize);
}
/********************************************************/



/**
 *
 */
/********************************************************/
void TouchPanel::SetHighPolar(void){
	taskENTER_CRITICAL();

	UpperRight.Write(true);
	UpperLeft.Write(true);
	LowerLeft.Write(true);
	LowerRight.Write(true);

	taskEXIT_CRITICAL();
	osDelay(SettlingTime_ms);
}
void TouchPanel::SetXPolar(void){
	taskENTER_CRITICAL();

	UpperRight.Write(true);
	LowerRight.Write(true);

	UpperLeft.Write(false);
	LowerLeft.Write(false);

	taskEXIT_CRITICAL();
	osDelay(SettlingTime_ms);
}
void TouchPanel::SetYPolar(void){
	taskENTER_CRITICAL();

	UpperRight.Write(true);
	UpperLeft.Write(true);

	LowerRight.Write(false);
	LowerLeft.Write(false);

	taskEXIT_CRITICAL();
	osDelay(SettlingTime_ms);
}
/********************************************************/



float TouchPanel::Average( const uint16_t* data, uint16_t size){
	uint32_t sum = 0;
	for(uint8_t i=0; i<size; i++) sum += data[i];

	return sum/(float)size;
}


/**
 *
 */
/********************************************************/
void TouchPanel::FilterInit(void){
	FilterX 	=  new MedianFilter(6,2);
	FilterY		=  new MedianFilter(6,2);
}
/********************************************************/

