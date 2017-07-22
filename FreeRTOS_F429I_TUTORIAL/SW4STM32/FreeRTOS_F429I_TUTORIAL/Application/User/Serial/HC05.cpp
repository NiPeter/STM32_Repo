/*
 * HC05.cpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */


#include "HC05.hpp"

/********************************************************/
void HC05::begin(){

}
/********************************************************/



/********************************************************/
HC05::HC05(UART_HandleTypeDef* huart, GPIO_TypeDef* key_port, uint16_t key_pin):
				hUART(huart),
				hKeyPort(key_port),
				keyPin(key_pin){

	osThreadDef(HC05, threadTask, osPriorityNormal, 0, 128);
	taskID = osThreadCreate(osThread(HC05), NULL);

};
/********************************************************/



/********************************************************/
void HC05::threadTask(void const * arguments){

	for(;;){

	}
}
/********************************************************/




