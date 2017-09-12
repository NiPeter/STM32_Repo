/*
 * ParallelPID.cpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#include "ParallelPID.hpp"



/**
 * @brief ParallelPID contructor
 */
ParallelPID::ParallelPID(float kp, float ki, float kd, float dt,
		IPerceptible *sensor, IControlable *actuator){

	Tune(kp,ki,kd);
	Sensor = sensor;
	Actuator = actuator;

	if(dt <= 0) dT = 0.01; //TODO dT <= 0 then EXCEPTON!
	else dT = dt;

	Stop();
	Reset();

}
/********************************************************/



/**
 * @brief PID process function
 * @note Process function should be called periodically with dT interval!
 */
void ParallelPID::Process() {

	if(Working == false) return;

	float pv = Sensor->Get(); // Get process Variable

	// Error computing
	float error = Setpoint - pv;				// proportional error
	float dError = (error - PrevError) / dT;	// derivative error
	SumError += error * dT ;					// integral error

	// Compute output
	ControlVariable = Kp * error + Ki * SumError + Kd * dError;

	// Store previous error
	PrevError = error;

	// Set output to actuator
	Actuator->Set(ControlVariable);

}
/********************************************************/



/**
 * @brief Start controller
 */
void ParallelPID::Start() {
	Working = true;
}
/********************************************************/



/**
 * @brief Stop controller
 */
void ParallelPID::Stop() {
	Working = false;
}
/********************************************************/



/**
 * @brief Reset controler internal state
 * @note This will not stop the controller!
 */
void ParallelPID::Reset() {
	Setpoint = 0;
	ControlVariable = 0;
	PrevError = 0;
	SumError = 0;
}
/********************************************************/
