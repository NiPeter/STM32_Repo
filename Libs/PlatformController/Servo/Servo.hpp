/*
 * Servo.hpp
 *
 *  Created on: 7 sie 2017
 *      Author: Peter
 */

#ifndef SERVO_HPP_
#define SERVO_HPP_

/***	Hardware STM32	***/
#include "stm32f4xx_hal.h"
#include "math.h"


/**
 * @brief Servo class declaration
 */
class Servo{
public:

	Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int freq_pwm = 50, unsigned int resolution = 2000);

	void Start( void );
	void Stop( void );

	void SetPos(float radians);
	float GetPos( void );

	void Calibrate(float min, float max);

private:

	/***	Variables	***/
	TIM_HandleTypeDef* 	hTIM;			// Timer handle
	uint16_t	 		Channel;		// Chanel handle

	float 				ms_min;			// 0 pulse time
	float 				ms_max;			// 180deg pulse time

	unsigned int 		Frequency;		// PWM frequency in HZ
	unsigned int		Resolution;		// PWM resolution

	/***	Functions	***/
	float radToMs( float angle);
	uint16_t msToCCR( float ms);

};
/********************************************************/

#endif /* SERVO_HPP_ */
