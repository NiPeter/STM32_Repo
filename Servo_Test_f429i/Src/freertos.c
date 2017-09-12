/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"

#ifdef __cplusplus
}
#endif

#include "PlatformController/PlatformController.hpp"
#include "TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"
#include "PID/ParallelPID/ParallelPID.hpp"
#include "Ball_Control/DOF.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId pidTaskHandle;

/* USER CODE BEGIN Variables */

Servo Servos[6] = {

		Servo(&htim4,TIM_CHANNEL_2),	// PB7 - Niebieski

		Servo(&htim3,TIM_CHANNEL_1),	// PB4 - Pomarañczowy
		Servo(&htim2,TIM_CHANNEL_2),	// PB3 - Fioletowy

		Servo(&htim9,TIM_CHANNEL_2), 	// PE6 - Br¹zowy
		Servo(&htim9,TIM_CHANNEL_1),	// PE5 - ¯ó³ty

		Servo(&htim3,TIM_CHANNEL_3),	// PC8 - Bia³y

};
Steward_Struct Steward = {
		{ 0.075, 	0.5236 	}, // Base_Struct {r , alpha}
		{ 0.05,		1.7453	}, // Platform_Struct {r , alpha}
		{ 0.01653,	0.095	}  // Drive_Struct {a , s}
};
PlatformController Controller(Servos,&Steward);
RollDOF Roll(Controller);
PitchDOF Pitch(Controller);

AnalogPin 	XAnalog(&hadc1,X_ADC_GPIO_Port,X_ADC_Pin);
AnalogPin 	YAnalog(&hadc2,Y_ADC_GPIO_Port,Y_ADC_Pin);
Pin			XGnd(X_GND_GPIO_Port,X_GND_Pin);
Pin			YGnd(Y_GND_GPIO_Port,Y_GND_Pin);
TouchPanel4W Panel(XAnalog,XGnd,YAnalog,YGnd);
XPlate XPos(Panel);
//YPlate YPos(Panel);


float kp = -0.00001;
float ki = 0;
float kd = 0;
float dt = 0.015;
float setpoint = 0;
ParallelPID XPid(kp,ki,kd,dt,&XPos,&Roll);



float X,Y;
int td,prev_td,td_inc;


float x,y,z,roll,pitch,yaw;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartPIDTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void StartProcedure(void);
void TouchPanelTask( void const * argument);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of pidTask */
  osThreadDef(pidTask, StartPIDTask, osPriorityRealtime, 0, 512);
  pidTaskHandle = osThreadCreate(osThread(pidTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	osThreadDef(touchPanelTask, TouchPanelTask, osPriorityAboveNormal, 0, 512);
	osThreadCreate(osThread(touchPanelTask), NULL);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */

	StartProcedure();

	XPid.Start();

	/* Infinite loop */
	for(;;)
	{
		prev_td = td;

		td = Panel.IsTouched();

		if( (prev_td == true) && (td == false) ) td_inc++;

		if(td){
			X = Panel.GetX();
			Y = Panel.GetY();
		}else{
			X = 0;
			Y = 0;
		}



		XPid.Tune(kp,ki,kd);
		XPid.SetInput(setpoint);

		Roll.Set(roll);
//		Pitch.Set(pitch);


//		uint8_t i = 0;
//		q[i++] = X/500.0;
//		q[i++] = Y/500.0;
//		q[i++] = z;
//		q[i++] = roll;
//		q[i++] = pitch;
//		q[i++] = yaw;
//
//		Controller.Move(q);

		osDelay(10);
	}
  /* USER CODE END StartDefaultTask */
}

/* StartPIDTask function */
void StartPIDTask(void const * argument)
{
  /* USER CODE BEGIN StartPIDTask */
	 const TickType_t xFrequency = 20;

	// TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialise the xLastWakeTime variable with the current time.

	while(true){
//		Panel.Process();
		XPid.Process();
		osDelay(xFrequency);
	}
  /* USER CODE END StartPIDTask */
}

/* USER CODE BEGIN Application */

void TouchPanelTask( void const * argument){
	 const TickType_t xFrequency = 10;

	 TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialise the xLastWakeTime variable with the current time.

	while(true){
		Panel.Process();
//		XPid.Process();
		osDelayUntil(&xLastWakeTime,xFrequency);
	}
}

void StartProcedure(void){
	Controller.Start();
	float q[6] = {0,0,0,0,0,0};
	Controller.Move(q);
	osDelay(500);
	q[2] = -0.005;
	Controller.Move(q);
	osDelay(500);
	q[2] = 0;
	Controller.Move(q);
	osDelay(500);

}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
