/*
 * hc_05.c
 *
 *  Created on: 19 maj 2017
 *      Author: Peter
 */

#include "main.h"
#include "stm32f4xx_hal.h"

#include "hc05.h"

/********************************************************
*	TYPES
********************************************************/

typedef enum {Data , Term_O, Term_K, Term_r, Term_n} Msg_State;

/********************************************************/




/********************************************************
*	VARIABLES
********************************************************/

#define TIMEOUT			10

static struct{
	UART_HandleTypeDef* huart; 	// handle to Bluetooth UART module structure
	GPIO_TypeDef* hgpio; 		// handle to Bluetooth KEY GPIO Port structure
	uint16_t key_pin;				// Bluetooth KEY Pin selected value
}BT_Conf;

/********************************************************/



/********************************************************
*	FUNCTIONS
********************************************************/

void BT_Init(UART_HandleTypeDef* huart,GPIO_TypeDef* key_port,uint16_t key_pin){

	BT_Conf.huart = huart;
	BT_Conf.hgpio = key_port;
	BT_Conf.key_pin = key_pin;

}

/* Single Char send/receive functions */
BT_StatusTypeDef BT_SendChar(const char* data){

	return HAL_UART_Transmit(BT_Conf.huart,(uint8_t*)data,1,TIMEOUT);
}

BT_StatusTypeDef BT_ReceiveChar(char* data){

	return HAL_UART_Receive(BT_Conf.huart,(uint8_t*)data,1,TIMEOUT);
}

/* Polling send/receive msg functions */
BT_StatusTypeDef BT_SendMsg(const char* msg){
	uint8_t size = strlen(msg);
	return HAL_UART_Transmit(BT_Conf.huart,(uint8_t*)msg,size,TIMEOUT);
}

//BT_StatusTypeDef BT_ReceiveMsg(char* msg){
//	Msg_State state = Data;
//
//	char data[30] = {0};
//	uint8_t index = 0;
//
//	while( state != Term_n ){
//
//		if( BT_ReceiveChar(&data[index]) == BT_TIMEOUT) return BT_TIMEOUT;
//
//		switch(state){
//		case Data:
//			if(data[index] == '\r') state = Term_r;
//			break;
//
//		case Term_r:
//			state = ( data[index] == '\n' ) ? Term_n : Data;
//			break;
//
//		default:
//			break;
//		}
//
//		if(++index==BT_MSG_SIZE) return BT_ERROR;
//	}
//
//	for( uint8_t i=0;i<30;i++){
//		msg[i] = data[i];
//	}
//
//	return BT_OK;
//
//
//}

/* Interrupt mode send/receive msg functions */
BT_StatusTypeDef BT_SendMsg_IT(char* msg, uint8_t len){
	return HAL_UART_Transmit_IT(BT_Conf.huart,(uint8_t *)msg,len);
}

BT_StatusTypeDef BT_ReceiveChar_IT(char* data){
	 return HAL_UART_Receive_IT(BT_Conf.huart, (uint8_t*)data, 1);
}

/* AT mode functions */
BT_StatusTypeDef BT_ReceiveAT(char* msg){
	Msg_State state = Data;

	char data[30] = {0};
	uint8_t index = 0;

	while( state != Term_n ){

		if( HAL_UART_Receive(BT_Conf.huart, (uint8_t*)&data[index], 1, TIMEOUT) == HAL_TIMEOUT) return BT_TIMEOUT;

		switch(state){
		case Data:
			if(data[index] == 'O') state = Term_O;
			break;

		case Term_O:
			state = ( data[index] == 'K' ) ? Term_K : Data;
			break;

		case Term_K:
			state = ( data[index] == '\r' ) ? Term_r : Data;
			break;

		case Term_r:
			state = ( data[index] == '\n' ) ? Term_n : Data;
			break;

		default:
			break;
		}
		if( !(++index<30) ) return BT_ERROR;
	}

	for( uint8_t i=0;i<30;i++){
		msg[i] = data[i];
	}

	return BT_OK;
}

void BT_ATmode(ATmode mode){
	GPIO_PinState keyState;

	if(mode == AT_On)keyState = GPIO_PIN_SET;
	else keyState = GPIO_PIN_RESET;

	HAL_GPIO_WritePin(BT_Conf.hgpio,BT_Conf.key_pin,keyState);
}

/********************************************************/


