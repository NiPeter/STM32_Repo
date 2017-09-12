/*
 * PID.hpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_PID_PID_HPP_
#define APPLICATION_USER_PID_PID_HPP_

#ifndef NULL
#define NULL   ((void *) 0)
#endif

class IPerceptible;
class IControlable;


class IPerceptible{
public:
	virtual ~IPerceptible(){};
	virtual float Get() = 0;
};


class IControlable{
public:
	virtual ~IControlable(){};
	virtual void Set(float value) = 0;
};



class PID{

public:

	virtual ~PID(){};

	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;

	void SetInput(float setpoint) {
		Setpoint = setpoint;
	};

	float GetOutput() const {
		return ControlVariable;
	};

	void Tune(float kp,float ki,float kd) {
		Kp = kp;
		Ki = ki;
		Kd = kd;
	}
	float GetKd() const {
		return Kd;
	}

	float GetKi() const {
		return Ki;
	}

	float GetKp() const {
		return Kp;
	}

protected:

	float Kp;
	float Ki;
	float Kd;

	float Setpoint;				// r(t)
	float ControlVariable;		// u(t)

	IPerceptible *Sensor;		//
	IControlable *Actuator;		// Plant / Process

};


#endif /* APPLICATION_USER_PID_PID_HPP_ */
