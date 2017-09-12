/*
 * PlatformController.hpp
 *
 *  Created on: 9 sie 2017
 *      Author: Peter
 */

#ifndef PLATFORMCONTROLLER_HPP_
#define PLATFORMCONTROLLER_HPP_

/***	MATLAB C Code Includes	***/
#ifdef __cplusplus
extern "C" {
#endif

#include "structInitFnc/structInitFnc.h"
#include "structInitFnc/structInitFnc_terminate.h"
#include "structInitFnc/structInitFnc_initialize.h"

#include "servoIK/servoIK.h"
#include "servoIK/servoIK_terminate.h"
#include "servoIK/servoIK_initialize.h"

#ifdef __cplusplus
}
#endif
/***	MATLAB C End	***/

#include "Servo/Servo.hpp"

class PlatformController{

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

	/***	Private Variables	***/
	Servo* servos[6];		// Servos handles
	IK_Struct IK;			// Inverse Kinematic Struct (contains all nessesary platform parameters)

	double Q[6];			// Desired platform Position and Orientation
	double Angles[6];		// Desired servo angles

	/***	Private Functions	***/
	void IKfun( void );
	void IKinit(Steward_Struct* steward);
	void SetPositions( void );

};



#endif /* PLATFORMCONTROLLER_HPP_ */
