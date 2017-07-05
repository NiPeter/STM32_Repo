/*
 * hc05.h
 *
 *  Created on: 20 maj 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_HC05_HC05_H_
#define APPLICATION_USER_HC05_HC05_H_

#include "stdlib.h"
#include "string.h"

#include "main.h"
#include "stm32f4xx_hal.h"

typedef enum {AT_Off, AT_On} ATmode;

typedef enum
{
  BT_OK       		= 0x00U,
  BT_ERROR    		= 0x01U,
  BT_TIMEOUT  		= 0x03U,
} BT_StatusTypeDef;



char data[30];

void BT_AT(void);
void BT_Init(UART_HandleTypeDef* huart,GPIO_TypeDef* key_port,uint16_t key_pin);

void BT_ATmode(ATmode mode);


BT_StatusTypeDef BT_SendChar(const char* data);
BT_StatusTypeDef BT_ReceiveChar(char* data);

BT_StatusTypeDef BT_SendMsg(const char* msg);
BT_StatusTypeDef BT_ReceiveMsg(char* msg);


BT_StatusTypeDef BT_SendMsg_IT(char* msg, uint8_t len);
BT_StatusTypeDef BT_ReceiveChar_IT(char* data);

BT_StatusTypeDef BT_ReceiveAT(char* msg);

#endif /* APPLICATION_USER_HC05_HC05_H_ */
