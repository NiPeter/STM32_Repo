/*
 * Servo.cpp
 *
 *  Created on: 7 sie 2017
 *      Author: Peter
 */

#include "Servo.hpp"


/**
 *
 * @param htim
 * @param channel
 */
/********************************************************/
Servo::Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int freq_pwm, unsigned int resolution)
:hTIM(htim),Channel(channel),Frequency(freq_pwm),Resolution(resolution){
	ms_min = 0.5;
	ms_max = 2.26;
}
/********************************************************/

/**
 *
 */
/********************************************************/
void Servo::start( void ){

	HAL_TIM_PWM_Start(hTIM,Channel);

}
/********************************************************/



/**
 *
 */
/********************************************************/
void Servo::stop( void ){

	HAL_TIM_PWM_Stop(hTIM,Channel);

}
/********************************************************/



/**
 *
 * @param deg
 */
/********************************************************/
void Servo::setPos(float radians){

	float ms = angToMs( radians );

	uint32_t CCR = msToCCR( ms );
	//__HAL_TIM_SET_COMPARE(hTIM,Channel,CCR);
	switch(Channel){
	case TIM_CHANNEL_1:
		hTIM->Instance->CCR1 = CCR;
		break;
	case TIM_CHANNEL_2:
		hTIM->Instance->CCR2 = CCR;
		break;
	case TIM_CHANNEL_3:
		hTIM->Instance->CCR3 = CCR;
		break;
	case TIM_CHANNEL_4:
		hTIM->Instance->CCR4 = CCR;
		break;
	}


}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float Servo::getPos( void ){
	uint32_t CCR;

	//CCR = __HAL_TIM_GET_COMPARE(hTIM,Channel);
	switch(Channel){
	case TIM_CHANNEL_1:
		CCR = hTIM->Instance->CCR1;
		break;
	case TIM_CHANNEL_2:
		CCR = hTIM->Instance->CCR2;
		break;
	case TIM_CHANNEL_3:
		CCR = hTIM->Instance->CCR3;
		break;
	case TIM_CHANNEL_4:
		CCR = hTIM->Instance->CCR4;
		break;
	}
	return CCR; //TODO
}
/********************************************************/


void Servo::calibrate(float min, float max){
	if( max <= min ) return;

	ms_min = min;
	ms_max = max;
}


/********************************************************/

float Servo::angToMs( float angle){
	float dms = ms_max - ms_min;

	return dms/(180.0)*angle + ms_min;
}

uint16_t Servo::msToCCR( float ms ){


	return ms*Frequency*Resolution/1000.0;

}
