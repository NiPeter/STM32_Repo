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
#include "CPU/cpu_utils.h"

#include "objects.hpp"


/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId bluetoothTxHandle;
osThreadId bluetoothRxHandle;
osThreadId touchPanelTaskHandle;
osSemaphoreId bluetoothTxSemaphoreHandle;
osSemaphoreId bluetoothRxSemaphoreHandle;
osSemaphoreId touchPanelADCSemaphoreHandle;

/* USER CODE BEGIN Variables */
uint8_t td;
float X,Y;
uint32_t adc;
size_t heap;
float cpu;
uint32_t inc;
uint8_t i;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartBluetoothTx(void const * argument);
void StartBluetoothRx(void const * argument);
void StartTouchPanelTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
__weak void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of bluetoothTxSemaphore */
  osSemaphoreDef(bluetoothTxSemaphore);
  bluetoothTxSemaphoreHandle = osSemaphoreCreate(osSemaphore(bluetoothTxSemaphore), 1);

  /* definition and creation of bluetoothRxSemaphore */
  osSemaphoreDef(bluetoothRxSemaphore);
  bluetoothRxSemaphoreHandle = osSemaphoreCreate(osSemaphore(bluetoothRxSemaphore), 1);

  /* definition and creation of touchPanelADCSemaphore */
  osSemaphoreDef(touchPanelADCSemaphore);
  touchPanelADCSemaphoreHandle = osSemaphoreCreate(osSemaphore(touchPanelADCSemaphore), 1);

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

  /* definition and creation of bluetoothTx */
  osThreadDef(bluetoothTx, StartBluetoothTx, osPriorityAboveNormal, 0, 128);
  bluetoothTxHandle = osThreadCreate(osThread(bluetoothTx), NULL);

  /* definition and creation of bluetoothRx */
  osThreadDef(bluetoothRx, StartBluetoothRx, osPriorityAboveNormal, 0, 128);
  bluetoothRxHandle = osThreadCreate(osThread(bluetoothRx), NULL);

  /* definition and creation of touchPanelTask */
  osThreadDef(touchPanelTask, StartTouchPanelTask, osPriorityAboveNormal, 0, 128);
  touchPanelTaskHandle = osThreadCreate(osThread(touchPanelTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	i = 20;
	/* Infinite loop */
	for(;;)
	{

		heap = xPortGetFreeHeapSize();
		cpu = osGetCPUUsage();



		bool beforeState = td;

		td = (Panel.IsTouched())? 23:0;

		if( (td==0) && (beforeState!=0) ) inc++;

		if( td ){
			X = Panel.GetX();
			Y = Panel.GetY();
			HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);
		}


		if(i!=0) osDelay(i);

	}
  /* USER CODE END StartDefaultTask */
}

/* StartBluetoothTx function */
void StartBluetoothTx(void const * argument)
{
  /* USER CODE BEGIN StartBluetoothTx */

	osSemaphoreWait(bluetoothTxSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(bluetoothTxSemaphoreHandle,osWaitForever);
		Bluetooth.processTxISR();
	}
  /* USER CODE END StartBluetoothTx */
}

/* StartBluetoothRx function */
void StartBluetoothRx(void const * argument)
{
  /* USER CODE BEGIN StartBluetoothRx */

	osSemaphoreWait(bluetoothRxSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(bluetoothRxSemaphoreHandle,osWaitForever);
		Bluetooth.processRxISR();
	}
  /* USER CODE END StartBluetoothRx */
}

/* StartTouchPanelTask function */
void StartTouchPanelTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchPanelTask */
	 TickType_t xLastWakeTime;
	 const TickType_t xFrequency = 10;
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	osSemaphoreWait(touchPanelADCSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
//		Panel.Process();
//		osDelayUntil(&xLastWakeTime,xFrequency);
		Panel.SetXPolar();
		Panel.SetYPolar();
		Panel.SetHighPolar();
	}
  /* USER CODE END StartTouchPanelTask */
}

/* USER CODE BEGIN Application */
void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc){

	Panel.ADC_ConvCpltCallback(hadc);
	adc = HAL_ADC_GetValue(hadc);

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(bluetoothTxSemaphoreHandle);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(bluetoothRxSemaphoreHandle);

}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
