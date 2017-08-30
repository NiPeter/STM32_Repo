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
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t upR, uint16_t upL, uint16_t loR, uint16_t loL,osSemaphoreId* semaphore):
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
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, Pin upR, Pin upL, Pin loR, Pin loL,osSemaphoreId* semaphore):
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

	bool tmpTouched;
	float tmpX,tmpY;
	tmpTouched = CheckTouch();

	if( !tmpTouched ){
		FilterX->Reset();
		FilterY->Reset();

		taskENTER_CRITICAL();
		Touched = tmpTouched;
		taskEXIT_CRITICAL();

		return;
	}

	tmpX = CheckX();
	tmpY = CheckY();

	taskENTER_CRITICAL();
		Touched = tmpTouched;
		if(tmpX != 0) X = tmpX;
		if(tmpY != 0) Y = tmpY;
	taskEXIT_CRITICAL();

}
/********************************************************/



/**
 *
 * @param hadc
 */
/********************************************************/
void TouchPanel::ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc){
	if(hadc->Instance == hADC->Instance){
		osSemaphoreRelease(*Semaphore);
	}
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
bool TouchPanel::CheckTouch( void ){

	SetHighPolar();
	if( Measure() > Treshold){
		return true;
	}
	else{
		return false;
	}
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float TouchPanel::CheckX(void){

	SetXPolar();
	return FilterX->Filter(Measure());
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float TouchPanel::CheckY(void){

	SetYPolar();
	return FilterY->Filter( Measure() );

}
/********************************************************/



/**
 *
 */
/********************************************************/
uint32_t TouchPanel::Measure(void){
	HAL_ADC_Start_IT(hADC);
	osSemaphoreWait(*Semaphore,osWaitForever);
	return HAL_ADC_GetValue(hADC);
}
/********************************************************/



/**
 *
 */
/********************************************************/
void TouchPanel::SetHighPolar(void){

	UpperRight.Write(true);
	UpperLeft.Write(true);
	LowerLeft.Write(true);
	LowerRight.Write(true);

	osDelay(SettlingTime_ms);
}
void TouchPanel::SetLowPolar(void){

	UpperRight.Write(false);
	UpperLeft.Write(false);
	LowerLeft.Write(false);
	LowerRight.Write(false);

	osDelay(SettlingTime_ms);
}
void TouchPanel::SetXPolar(void){

	UpperRight.Write(true);
	LowerRight.Write(true);

	UpperLeft.Write(false);
	LowerLeft.Write(false);

	osDelay(SettlingTime_ms);
}
void TouchPanel::SetYPolar(void){

	UpperRight.Write(true);
	UpperLeft.Write(true);

	LowerRight.Write(false);
	LowerLeft.Write(false);

	osDelay(SettlingTime_ms);
}
/********************************************************/



/**
 *
 * @param data
 * @param size
 * @return
 */
/********************************************************/
float TouchPanel::Average( const uint16_t data[], uint16_t size){
	uint32_t sum = 0;
	for(uint8_t i=0; i<size; i++) sum += data[i];

	return sum/(float)size;
}
/********************************************************/




/**
 *
 */
/********************************************************/
void TouchPanel::FilterInit(void){
	FilterX 	=  new MedianFilter(17,3);
	FilterY		=  new MedianFilter(17,3);
}
/********************************************************/

