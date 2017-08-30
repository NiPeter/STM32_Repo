/*
 * Pin.hpp
 *
 *  Created on: 29 sie 2017
 *      Author: Peter
 */

#ifndef DRIVERS_TOUCHPANEL_4W_PIN_HPP_
#define DRIVERS_TOUCHPANEL_4W_PIN_HPP_

#include "stm32f4xx_hal.h"

class Pin;
class AnalogPin;

enum  PullUp_e{ NoPull = GPIO_NOPULL, PullUp = GPIO_PULLUP, PullDown = GPIO_PULLDOWN};

class Pin{

	friend class AnalogPin;

	GPIO_TypeDef*		hGPIO;
	uint16_t			nPIN;
	enum { None, Analog , Input, Output }		Mode;

public:

	Pin(GPIO_TypeDef* hgpio, uint16_t pin);
	Pin(Pin &pin);

	void Write(bool state);
	void Toggle(void);
	bool Read(void);

	void SetOutputMode(  PullUp_e pull = NoPull);
	void SetInputMode(  PullUp_e pull = NoPull );

};




/********************************************************/
class AnalogPin : public Pin{

	ADC_HandleTypeDef* 					hADC;


public:

	AnalogPin(ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t pin);

	void SetAnalogMode(void);

	void Measure_IT(void);
	void Measure(void);

	uint32_t GetADCValue(void);
	ADC_HandleTypeDef* GetADC_Handle(void);
};
/********************************************************/

#endif /* DRIVERS_TOUCHPANEL_4W_PIN_HPP_ */
