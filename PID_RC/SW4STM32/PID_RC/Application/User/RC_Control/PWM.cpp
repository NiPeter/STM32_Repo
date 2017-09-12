/*
 * PWM.cpp
 *
 *  Created on: 7 wrz 2017
 *      Author: Peter
 */

#include "PWM.h"

PWM::PWM(TIM_HandleTypeDef *htim, uint16_t channel, uint16_t period) {
	hTIM = htim;
	Channel = channel;
	Period = period;
}

PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

void PWM::Set(float value) {

	uint16_t CCR = value * Period / 100.0;
	__HAL_TIM_SET_COMPARE(hTIM,Channel,CCR);

}
