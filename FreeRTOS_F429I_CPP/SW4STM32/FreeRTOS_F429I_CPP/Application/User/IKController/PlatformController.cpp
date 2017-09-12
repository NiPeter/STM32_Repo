/*
 * PlatformController.cpp
 *
 *  Created on: 9 sie 2017
 *      Author: Peter
 */

#include "PlatformController.hpp"

inline float rad2deg(float angle){
	return angle*180/M_PI;
}
inline float deg2rad(float angle){
	return M_PI/180*angle;
}

/**
 *
 * @param servo
 * @param steward
 */
/********************************************************/
PlatformController::PlatformController(Servo servo[6],Steward_Struct* steward){
	for(int i=0;i<6;i++) servos[i] = &servo[i];

	Stop();
	IKinit(steward);
}
/********************************************************/



/**
 *
 * @param servo1
 * @param servo2
 * @param servo3
 * @param servo4
 * @param servo5
 * @param servo6
 * @param steward
 */
/********************************************************/
PlatformController::PlatformController(Servo* servo1, Servo* servo2, Servo* servo3, Servo* servo4, Servo* servo5, Servo* servo6,Steward_Struct* steward){
	servos[0] = servo1;
	servos[1] = servo2;
	servos[2] = servo3;
	servos[3] = servo4;
	servos[4] = servo5;
	servos[5] = servo6;

	Stop();
	IKinit(steward);
}
/********************************************************/



/**
 *
 * @param x
 * @param y
 * @param z
 */
/********************************************************/
void PlatformController::Translate( float x, float y, float z){
	Q[0] = x;
	Q[1] = y;
	Q[2] = z;

	IKfun();
	SetPositions();
}
/********************************************************/
void PlatformController::X(float x){
	Translate(x,Q[1],Q[2]);
}
void PlatformController::Y(float y){
	Translate(Q[0],y,Q[2]);
}
void PlatformController::Z(float z){
	Translate(Q[0],Q[1],z);
}
/********************************************************/



/**
 *
 * @param roll
 * @param pitch
 * @param yaw
 */
/********************************************************/
void PlatformController::Rotate( float roll, float pitch, float yaw){
	Q[3] = roll;
	Q[4] = pitch;
	Q[5] = yaw;

	IKfun();
	SetPositions();
}
/********************************************************/
void PlatformController::Roll( float roll ){
	Rotate(roll,Q[4],Q[5]);
}
void PlatformController::Pitch( float pitch ){
	Rotate(Q[3],pitch,Q[5]);
}
void PlatformController::Yaw( float yaw ){
	Rotate(Q[3],Q[4],yaw);
}
/********************************************************/



/**
 *
 * @param q
 */
/********************************************************/
void PlatformController::Move( float q[6]){

	for(uint8_t i=0; i<6 ; i++) Q[i] = q[i];

	IKfun();
	SetPositions();
}
/********************************************************/


/**
 *
 */
/********************************************************/
void PlatformController::Start( void ){
	for( uint8_t i=0 ; i<6 ; i++) servos[i]->start();
}
void PlatformController::Stop( void ){
	for( uint8_t i=0 ; i<6 ; i++) servos[i]->stop();
}
/********************************************************/



/**
 *
 * @param angles
 */
/********************************************************/
void PlatformController::GetAngles(float angles[6]){
	for( uint8_t i=0; i<6; i++) angles[i] = Angles[i];
}
void PlatformController::GetQ(float q[6]){
	for( uint8_t i=0; i<6; i++) q[i] = Q[i];
}
/********************************************************/




/***	PRIVATE FUNCTIONS	***/

/**
 *
 */
/********************************************************/
void PlatformController::IKfun(){


	for(int i=0; i<3 ; i++) Q[i] = Q[i]/1000.0;
	for(int i=3; i<6 ; i++) Q[i] = deg2rad(Q[i]);

	servoIK(Q, &IK, Angles);

	for(int i =0;i<6;i++){
		if((i==0) || (i==2) ||(i==4)){ //nieparzyste
			Angles[i] = -Angles[i] + M_PI_2;
		}else{
			Angles[i] = Angles[i] - M_PI_2;
			Angles[i] = M_PI - Angles[i];
		}
	}

}
/********************************************************/



/**
 *
 */
/********************************************************/
void PlatformController::SetPositions( void ){



	for( uint8_t i=0; i<6; i++)
		servos[i]->setPos(Angles[i]);

}
/********************************************************/

void PlatformController::IKinit(Steward_Struct* steward){



	structInitFnc_initialize();
	servoIK_initialize();

	structInitFnc(steward,(struct0_T*)&IK);


}
