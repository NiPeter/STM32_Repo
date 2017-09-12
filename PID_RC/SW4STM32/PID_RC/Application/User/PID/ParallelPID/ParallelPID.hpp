/*
 * ParallelPID.hpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_
#define APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_

#include "../PID.hpp"

class ParallelPID : public PID{

public:

	ParallelPID(float kp, float ki, float kd, float dt, IPerceptible *sensor, IControlable *actuator);

	void Process();

	void Start();
	void Stop();
	void Reset();

	float GetT() const {
		return dT;
	}

	bool IsWorking() const {
		return Working;
	}

private:

	float dT;
	float PrevError;
	float SumError;
	bool Working;	// True if working

};


#endif /* APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_ */
