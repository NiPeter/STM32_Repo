/*
 * Potentiometer.cpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#include "Potentiometer.h"


Potentiometer::Potentiometer(AnalogPin &pin,IFilter<float,float> *filter) : Pin(pin),Filter(filter){
	Pin.SetAnalogMode();
}

Potentiometer::~Potentiometer() {
	// TODO Auto-generated destructor stub
}

float Potentiometer::Get() {
	Pin.Measure();
	HAL_ADC_PollForConversion(Pin.GetADC_Handle(),100);
	uint32_t value = Pin.GetADCValue();

	return Filter->Filter(value*100.0/4095);
}
