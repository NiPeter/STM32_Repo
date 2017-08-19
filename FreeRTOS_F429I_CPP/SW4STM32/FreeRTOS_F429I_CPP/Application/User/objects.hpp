/*
 * objects.hpp
 *
 *  Created on: 15 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_OBJECTS_HPP_
#define APPLICATION_USER_OBJECTS_HPP_



/***	INCLUDES	***/

#include "usart.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

#include "HC05.hpp"
#include "Communicator.hpp"

#include "Servo.hpp"
#include "PlatformController.hpp"

#include "TouchPanel.hpp"


/***	***	***		***/



/********************************************************/
/********************************************************/

extern HC05 Bluetooth;

extern Communicator Comm;

extern Servo Servos[6];

extern Steward_Struct steward;

extern PlatformController Controller;

extern TouchPanel Panel;

/********************************************************/
/********************************************************/



#endif /* APPLICATION_USER_OBJECTS_HPP_ */
