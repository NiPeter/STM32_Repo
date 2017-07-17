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

/***	STM INCLUDES	***/
#include "main.h"
#include "stm32f4xx_hal.h"

/***	COMMUNICATION INCLUDES	***/
#include "hc05.h"
#include "cmd_protocol.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId commandExecuterTaskHandle;
osThreadId commRxTaskHandle;
osThreadId commTxTaskHandle;
osMessageQId cmdQueueHandle;
osMessageQId commRxQueueHandle;
osMessageQId commTxQueueHandle;
osSemaphoreId commTxSemaphoreHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartCommandExecuterTask(void const * argument);
void StartCommRxTask(void const * argument);
void StartCommTxTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void ErrorBlink(void);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of commTxSemaphore */
  osSemaphoreDef(commTxSemaphore);
  commTxSemaphoreHandle = osSemaphoreCreate(osSemaphore(commTxSemaphore), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of commandExecuterTask */
  osThreadDef(commandExecuterTask, StartCommandExecuterTask, osPriorityAboveNormal, 0, 128);
  commandExecuterTaskHandle = osThreadCreate(osThread(commandExecuterTask), NULL);

  /* definition and creation of commRxTask */
  osThreadDef(commRxTask, StartCommRxTask, osPriorityHigh, 0, 128);
  commRxTaskHandle = osThreadCreate(osThread(commRxTask), NULL);

  /* definition and creation of commTxTask */
  osThreadDef(commTxTask, StartCommTxTask, osPriorityHigh, 0, 128);
  commTxTaskHandle = osThreadCreate(osThread(commTxTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of cmdQueue */
  osMessageQDef(cmdQueue, 20, Command_TypeDef);
  cmdQueueHandle = osMessageCreate(osMessageQ(cmdQueue), NULL);

  /* definition and creation of commRxQueue */
  osMessageQDef(commRxQueue, 1, char*);
  commRxQueueHandle = osMessageCreate(osMessageQ(commRxQueue), NULL);

  /* definition and creation of commTxQueue */
  osMessageQDef(commTxQueue, 10, char*);
  commTxQueueHandle = osMessageCreate(osMessageQ(commTxQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	size_t i;
	/* Infinite loop */
	for(;;)
	{
		HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);

		char *msg_ptr = pvPortMalloc(20);
		i = xPortGetFreeHeapSize();
		sprintf(msg_ptr,"Default Task: %i\r\n",i);
		osMessagePut(commTxQueueHandle,(uint32_t)msg_ptr,0);

		osDelay(1000);
	}
  /* USER CODE END StartDefaultTask */
}

/* StartCommandExecuterTask function */
void StartCommandExecuterTask(void const * argument)
{
  /* USER CODE BEGIN StartCommandExecuterTask */
	Command_TypeDef cmd;

  /* Infinite loop */
  for(;;)
  {

	xQueueReceive(cmdQueueHandle,&cmd,portMAX_DELAY);

	char *msg_ptr = pvPortMalloc(30);
	if(msg_ptr == NULL ) ErrorBlink();

	CP_PackMsg(cmd,msg_ptr);

    osMessagePut(commTxQueueHandle,(uint32_t)msg_ptr,0);

  }
  /* USER CODE END StartCommandExecuterTask */
}

/* StartCommRxTask function */
void StartCommRxTask(void const * argument)
{
  /* USER CODE BEGIN StartCommRxTask */
	osEvent event;
	char* msg;
	CommandList_TypeDef cmdList;

	BT_ReceiveChar_IT(); // Start BT

  /* Infinite loop */
  for(;;)
  {

	  event = osMessageGet(commRxQueueHandle,osWaitForever);
	  if(event.status != osEventMessage) ErrorBlink();

	  msg = event.value.p;
	  CP_UnpackMsg(msg,&cmdList);

	  for(uint8_t i=0; i<cmdList.Cnt; i++){
		Command_TypeDef cmd = cmdList.CmdBuff[i];
  	    xQueueSendToBack(cmdQueueHandle,&cmd,100);
	  }

	  HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);

  }
  /* USER CODE END StartCommRxTask */
}

/* StartCommTxTask function */
void StartCommTxTask(void const * argument)
{
  /* USER CODE BEGIN StartCommTxTask */
	osEvent event;
	char *msg_ptr = NULL;

  /* Infinite loop */
  for(;;)
  {
	osSemaphoreWait(commTxSemaphoreHandle,osWaitForever);
	vPortFree(msg_ptr);

	event = osMessageGet(commTxQueueHandle,osWaitForever);
    if(event.status != osEventMessage) ErrorBlink();

    msg_ptr = event.value.p;
    BT_SendMsg_IT(msg_ptr);
  }
  /* USER CODE END StartCommTxTask */
}

/* USER CODE BEGIN Application */
     
void ErrorBlink( void ){
	while(1){
		HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
		HAL_Delay(300);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == BT_GetInstance()){
		osSemaphoreRelease(commTxSemaphoreHandle);
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	static char msg_buff[CP_MSG_SIZE];

	if(huart->Instance == BT_GetInstance()){

		osStatus queueStatus;

		CP_StatusTypeDef msgStatus = CP_ComposeMsg(BT_GetRxChar(),msg_buff);

		if(msgStatus == CP_MSG_READY) {
			queueStatus = osMessagePut(commRxQueueHandle,(uint32_t)msg_buff,0);
			if(queueStatus != osOK) ErrorBlink(); // TODO Add some response to full queue problem
		}

		BT_ReceiveChar_IT();

	}

}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
