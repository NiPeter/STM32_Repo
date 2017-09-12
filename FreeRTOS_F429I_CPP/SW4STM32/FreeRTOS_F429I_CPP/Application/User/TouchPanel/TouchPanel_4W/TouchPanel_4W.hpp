/*
 * TouchPanel_4W.hpp
 *
 *  Created on: 29 sie 2017
 *      Author: Peter
 */

#ifndef DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_
#define DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"


#include "../Filters/MedianFilter/MedianFilter.hpp"
#include "../ITouchPanel.hpp"
#include "Pin.hpp"

class TouchPanel4W : public ITouchPanel{

AnalogPin 		&XAnalog,	&YAnalog;
Pin				&XGnd,		&YGnd;

IFilter<float,float>		*XFilter;
IFilter<float,float>		*YFilter;

public:
	TouchPanel4W(AnalogPin &x_analog, Pin &x_gnd, AnalogPin &y_analog, Pin &y_gnd);

	void Process(void);
	void ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc);

private:

	void PrepareTouchDetection();
	void PrepareMeasurement(AnalogPin &analog, Pin &vcc, Pin &gnd, Pin &hiZ);
	void PrepareXMeasurement();
	void PrepareYMeasurement();

	uint32_t MeasureX();
	uint32_t MeasureY();

	void InitFilters();

};

#endif /* DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_ */