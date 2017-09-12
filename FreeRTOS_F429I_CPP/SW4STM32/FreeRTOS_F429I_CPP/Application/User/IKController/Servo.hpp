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
#include "math.h"

class Servo{
private:
	TIM_HandleTypeDef* 	hTIM;
	uint16_t	 		Channel;
	float 				ms_min;			// 0deg pulse time
	float 				ms_max;			// 180deg pulse time

	unsigned int 		Frequency;		// PWM frequency in HZ
	unsigned int		Resolution;		// PWM resolution

public:
	Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int freq_pwm = 50, unsigned int resolution = 2000);

	void start( void );
	void stop( void );

	void setPos(float radians);
	float getPos( void );

	void calibrate(float min, float max);

private:
	float angToMs( float angle);
	uint16_t msToCCR( float ms);

};

#endif /* APPLICATION_USER_IKCONTROLLER_SERVO_HPP_ */
