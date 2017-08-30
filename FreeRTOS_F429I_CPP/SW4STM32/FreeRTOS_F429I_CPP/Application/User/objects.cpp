/*
 * objects.cpp
 *
 *  Created on: 15 sie 2017
 *      Author: Peter
 */

#include "objects.hpp"

/********************************************************/

HC05 Bluetooth(&huart1);

Communicator Comm(&Bluetooth);

/********************************************************/




/********************************************************/

Servo Servos[6] = {
		Servo(&htim2,TIM_CHANNEL_2),
		Servo(&htim3,TIM_CHANNEL_1),
		Servo(&htim4,TIM_CHANNEL_2),
		Servo(&htim3,TIM_CHANNEL_3),
		Servo(&htim9,TIM_CHANNEL_1),
		Servo(&htim9,TIM_CHANNEL_2)
};


Steward_Struct Steward = {
		{ 0.075, 	0.5236 	}, // Base_Struct {r , alpha}
		{ 0.05,		1.7453	}, // Platform_Struct {r , alpha}
		{ 0.01653,	0.095	}  // Drive_Struct {a , s}
};

PlatformController Controller(Servos,&Steward);

/********************************************************/



/********************************************************/

extern osSemaphoreId touchPanelADCSemaphoreHandle;
TouchPanel Panel(&hadc1,GPIOD,UR_Pin,UL_Pin,LR_Pin,LL_Pin,&touchPanelADCSemaphoreHandle);

/********************************************************/


