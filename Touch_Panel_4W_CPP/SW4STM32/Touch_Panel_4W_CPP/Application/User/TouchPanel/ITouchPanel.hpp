/*
 * TouchPanel.hpp
 *
 *  Created on: 16 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_TOUCHPANEL_ITOUCHPANEL_HPP_
#define APPLICATION_USER_TOUCHPANEL_ITOUCHPANEL_HPP_


#include "stm32f4xx_hal.h"


/********************************************************/
class ITouchPanel{

protected:
/***	Variables  	***/
	__IO float X;
	__IO float Y;
	__IO bool Touched;

public:

	virtual ~ITouchPanel(void){};

	bool IsTouched( void ) {return Touched;};
	float GetX(void){return X;};
	float GetY(void){return Y;};

	virtual void Process(void) = 0;
	virtual void ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc) = 0;

};
/********************************************************/

#endif /* APPLICATION_USER_TOUCHPANEL_ITOUCHPANEL_HPP_ */
