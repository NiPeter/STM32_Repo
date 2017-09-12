/*
 * TouchPanel.cpp
 *
 *  Created on: 16 sie 2017
 *      Author: Peter
 */

#include "../TouchPanel_OLD/TouchPanel.hpp"



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
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t upR, uint16_t upL, uint16_t loR, uint16_t loL):
hADC(hadc),UpperLeft(hgpio,upL),UpperRight(hgpio,upR),LowerLeft(hgpio,loL),LowerRight(hgpio,loR){
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
TouchPanel::TouchPanel( ADC_HandleTypeDef* hadc, Pin upR, Pin upL, Pin loR, Pin loL):
						hADC(hadc),UpperLeft(upL),UpperRight(upR),LowerLeft(loL),LowerRight(loR){
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


	if( !CheckTouch() ){
		FilterX->Reset();
		FilterY->Reset();
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

//	uint16_t data[BufferSize];

	uint32_t value;

	SetHighPolar();
	Measure();

	value = HAL_ADC_GetValue(hADC);

	if(value > Treshold){
		Touched = true;
		return true;
	}
	else{
		Touched = false;
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
	uint16_t data[BufferSize];

	for(uint8_t i=0; i<BufferSize; i++ ){
		Measure();

		data[i] = HAL_ADC_GetValue(hADC);
	}

	float value = Average(data,BufferSize);

	value = FilterX->Filter(value);

	if(value != 0) X = value;

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
	uint16_t data[BufferSize];

	for(uint8_t i=0; i<BufferSize; i++ ){
		Measure();

		data[i] = HAL_ADC_GetValue(hADC);
	}

	float value = Average(data,BufferSize);

	value = FilterY->Filter(value);

	if(value != 0) Y = value;

	//	Measure();
	//	FilterY->Reset();
	//	osSemaphoreWait(Semaphore,osWaitForever);
	//
	//	for(uint8_t i=0; i<BufferSize-1; i++){
	//		FilterY->Filter( Data[i] );
	//	}
	//	float value = FilterY->Filter( Data[BufferSize-1] );
	//
	//	Y = value;
	////	osSemaphoreWait(Semaphore,osWaitForever);
	////	float value = Average(Data,BufferSize);
	////
	////	value = FilterY->Filter(value);
	////
	////	if(value != 0) Y = value;

	return Y;

}
/********************************************************/


/**
 *
 */
/********************************************************/
void TouchPanel::Measure(void){
	HAL_ADC_Start_IT(hADC);
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


	HAL_Delay(SettlingTime_ms);
}
void TouchPanel::SetXPolar(void){


	UpperRight.Write(true);
	LowerRight.Write(true);

	UpperLeft.Write(false);
	LowerLeft.Write(false);


	HAL_Delay(SettlingTime_ms);
}
void TouchPanel::SetYPolar(void){


	UpperRight.Write(true);
	UpperLeft.Write(true);

	LowerRight.Write(false);
	LowerLeft.Write(false);


	HAL_Delay(SettlingTime_ms);
}
/********************************************************/



float TouchPanel::Average( const uint16_t data[], uint16_t size){
	uint32_t sum = 0;
	for(uint8_t i=0; i<size; i++) sum += data[i];

	return sum/(float)size;
}


/**
 *
 */
/********************************************************/
void TouchPanel::FilterInit(void){
	FilterX 	=  new MedianFilter(10,2);
	FilterY		=  new MedianFilter(10,2);
	FilterT		=  new MedianFilter(BufferSize,2);
}
/********************************************************/

