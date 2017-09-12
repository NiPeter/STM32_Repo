/*
 * PWM.h
 *
 *  Created on: 7 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_RC_CONTROL_PWM_H_
#define APPLICATION_USER_RC_CONTROL_PWM_H_

#include "stm32f4xx_hal.h"
#include "../PID/PID.hpp"

/*
 *
 */
class PWM: public IControlable {
	TIM_HandleTypeDef* 	hTIM;
	uint16_t	 		Channel;
	uint16_t 			Period;
public:
	PWM(TIM_HandleTypeDef *htim, uint16_t channel, uint16_t period);
	virtual ~PWM();

	void Start() { 	HAL_TIM_PWM_Start(hTIM,Channel); };
	void Stop() { 	HAL_TIM_PWM_Stop(hTIM,Channel); };
	void Set(float value);
};

#endif /* APPLICATION_USER_RC_CONTROL_PWM_H_ */
