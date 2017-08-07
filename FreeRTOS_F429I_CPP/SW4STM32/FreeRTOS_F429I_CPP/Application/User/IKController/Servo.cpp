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
	ms_min = 0;
	ms_max = 1.5;
}
/********************************************************/

/**
 *
 */
/********************************************************/
void Servo::Start( void ){

	HAL_TIM_PWM_Start(hTIM,Channel);

}
/********************************************************/



/**
 *
 */
/********************************************************/
void Servo::Stop( void ){

	HAL_TIM_PWM_Stop(hTIM,Channel);

}
/********************************************************/



/**
 *
 * @param deg
 */
/********************************************************/
void Servo::SetPos(float deg){
	uint16_t CCR;

	CCR = MsToCCR( AngToMs( deg ) );
	__HAL_TIM_SET_COMPARE(hTIM,Channel,CCR);
}
/********************************************************/



/**
 *
 * @return
 */
/********************************************************/
float Servo::GetPos( void ){
	uint16_t CCR;

	CCR = __HAL_TIM_GET_COMPARE(hTIM,Channel);
	return CCR; //TODO
}
/********************************************************/





float Servo::AngToMs( float angle){
	float dms = ms_max - ms_min;

	return dms/180.0*angle + ms_min;
}

uint16_t Servo::MsToCCR( float ms ){


	return ms*Frequency*Resolution/1000.0;

}
