/*
 * objects.hpp
 *
 *  Created on: 15 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_OBJECTS_HPP_
#define APPLICATION_USER_OBJECTS_HPP_



/***	INCLUDES	***/

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#ifdef __cplusplus
}
#endif

#include "HC05.hpp"
#include "Communicator.hpp"

#include "Servo.hpp"
#include "PlatformController.hpp"

#include "TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"


/***	***	***		***/



/********************************************************/
/********************************************************/

extern HC05 Bluetooth;

extern Communicator Comm;

extern Servo Servos[6];

extern Steward_Struct steward;

extern PlatformController Controller;

extern TouchPanel4W Panel;

/********************************************************/
/********************************************************/



#endif /* APPLICATION_USER_OBJECTS_HPP_ */
