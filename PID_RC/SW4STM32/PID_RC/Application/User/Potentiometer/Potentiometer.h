/*
 * Potentiometer.h
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_POTENTIOMETER_H_
#define APPLICATION_USER_POTENTIOMETER_H_

#include "../PID/PID.hpp"
#include "Pin.hpp"
#include "../Filters/MedianFilter/MedianFilter.hpp"

/*
 *
 */
class Potentiometer: public IPerceptible {
	AnalogPin Pin;
	IFilter<float,float> *Filter;
public:
	Potentiometer(AnalogPin &pin,IFilter<float,float> *filter);
	virtual ~Potentiometer();
	float Get();

};

#endif /* APPLICATION_USER_POTENTIOMETER_H_ */
