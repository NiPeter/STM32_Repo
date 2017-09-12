/*
 * PlatformController.hpp
 *
 *  Created on: 9 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_IKCONTROLLER_PLATFORMCONTROLLER_HPP_
#define APPLICATION_USER_IKCONTROLLER_PLATFORMCONTROLLER_HPP_

#include "Servo.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "structInitFnc.h"
#include "structInitFnc_terminate.h"
#include "structInitFnc_initialize.h"

#include "servoIK.h"
#include "servoIK_terminate.h"
#include "servoIK_initialize.h"

#ifdef __cplusplus
}
#endif

class PlatformController{
private:
	Servo* servos[6];
	IK_Struct IK;

	double Q[6];
	double Angles[6];

public:

	PlatformController(Servo servo[6],Steward_Struct* steward);
	PlatformController(Servo* servo1, Servo* servo2, Servo* servo3, Servo* servo4, Servo* servo5, Servo* servo6, Steward_Struct* steward);

	// Units - deg and mm
	void Translate( float x, float y, float z);
	void X( float x );
	void Y( float y );
	void Z( float z );

	void Rotate( float roll, float pitch, float yaw);
	void Roll( float roll );
	void Pitch( float pitch );
	void Yaw( float yaw );

	void Move( float q[6]);

	void Start( void );
	void Stop( void );

	void GetAngles(float angles[6]);
	void GetQ( float q[6]);

private:

	void IKfun( void );
	void IKinit(Steward_Struct* steward);
	void SetPositions( void );

};



#endif /* APPLICATION_USER_IKCONTROLLER_PLATFORMCONTROLLER_HPP_ */
