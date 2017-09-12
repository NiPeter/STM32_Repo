/*
 * Servo.cpp
 *
 *  Created on: 7 sie 2017
 *      Author: Peter
 */

#include "Servo.hpp"


/**
 * @brief Servo class constructor
 * @param htim
 * @param channel
 */
Servo::Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int freq_pwm, unsigned int resolution)
:hTIM(htim),Channel(channel),Frequency(freq_pwm),Resolution(resolution){
	ms_min = 0.5;
	ms_max = 2.26;
}
/********************************************************/



/**
 * @brief Start servo control.
 * @note Start PWM generation on servo`s signal pin.
 */
void Servo::Start( void ){

	HAL_TIM_PWM_Start(hTIM,Channel);

}
/********************************************************/



/**
 * @brief Stop servo control.
 * @note Servo will be not responding to any SetPos() commands.
 */
void Servo::Stop( void ){

	HAL_TIM_PWM_Stop(hTIM,Channel);

}
/********************************************************/



/**
 * @brief Set the angle of the servo`s shaft.
 * @note Angle unit is radian!
 * @param radians
 */
void Servo::SetPos(float radians){

	float ms = radToMs( radians );
	uint32_t CCR = msToCCR( ms );

	__HAL_TIM_SET_COMPARE(hTIM,Channel,CCR);
}
/********************************************************/



/**
 * @brief Return currently set position
 * @return
 */
float Servo::GetPos( void ){
	uint32_t CCR;

	CCR = __HAL_TIM_GET_COMPARE(hTIM,Channel);
	return CCR; //TODO Return position
}
/********************************************************/



/**
 * @brief Write new min and max pulse time
 * @note Time unit is ms!
 * @param min - pulse time for 0 angle
 * @param max - pulse time for PI angle
 */
void Servo::Calibrate(float min, float max){
	if( max <= min ) return;
	ms_min = min;
	ms_max = max;
}
/********************************************************/


/********************************************************/
/********************************************************/



/**
 * @brief Convert given angle from the radians to the corresponding pulse time in ms
 * @note Angle unit is radian!
 * @param angle
 * @return
 */
float Servo::radToMs( float angle ){
	float dms = ms_max - ms_min;

	return dms/(M_PI)*angle + ms_min;
}
/********************************************************/


/**
 * @brief Convert given pulse time from ms to corresponding value in timer`s CCR register
 * @param ms
 * @return
 */
uint16_t Servo::msToCCR( float ms ){


	return ms*Frequency*Resolution/1000.0;

}
/********************************************************/
