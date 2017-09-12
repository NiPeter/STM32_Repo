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

	uint16_t CCR = msToCCR( ms );
	__HAL_TIM_SET_COMPARE(hTIM,Channel,CCR);
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float Servo::getPos( void ){
	uint16_t CCR;

	CCR = __HAL_TIM_GET_COMPARE(hTIM,Channel);
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
