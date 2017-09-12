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

enum  	PushPull_e	{ NoPull = GPIO_NOPULL, PullUp = GPIO_PULLUP, PullDown = GPIO_PULLDOWN};
enum 	PinMode_e	{ None, Analog , Input, Output };

class Pin{

	friend class AnalogPin;

	GPIO_TypeDef*		hGPIO;
	uint16_t			nPIN;

	PinMode_e			Mode;

public:

	Pin(GPIO_TypeDef* hgpio, uint16_t pin, PinMode_e mode = Input, PushPull_e  pull = NoPull);
	Pin(Pin &pin);

	void Write(bool state);
	void Toggle(void);
	bool Read(void);

	PinMode_e GetMode() {return Mode;};

	void SetOutputMode(  PushPull_e pull = NoPull);
	void SetInputMode(  PushPull_e pull = NoPull );



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
