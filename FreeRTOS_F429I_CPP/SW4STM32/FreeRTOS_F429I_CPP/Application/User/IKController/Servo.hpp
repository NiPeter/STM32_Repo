/*
 * Servo.hpp
 *
 *  Created on: 7 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_IKCONTROLLER_SERVO_HPP_
#define APPLICATION_USER_IKCONTROLLER_SERVO_HPP_

/***	Hardware STM32	***/
#include "stm32f4xx_hal.h"


class Servo{
private:
	TIM_HandleTypeDef* 	hTIM;
	uint16_t	 		Channel;
	float 				ms_min;			// 0deg pulse time
	float 				ms_max;			// 180deg pulse time

	unsigned int 		Frequency;		// PWM frequency in HZ
	unsigned int		Resolution;		// PWM resolution

public:
	Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int freq_pwm, unsigned int resolution = 1000);

	void Start( void );
	void Stop( void );

	void SetPos(float deg);
	float GetPos( void );

private:
	float AngToMs( float angle);
	uint16_t MsToCCR( float ms);

};

#endif /* APPLICATION_USER_IKCONTROLLER_SERVO_HPP_ */
