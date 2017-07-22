/*
 * HC05.hpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_SERIAL_HC05_HPP_
#define APPLICATION_USER_SERIAL_HC05_HPP_

#include "Serial.hpp"

/***	Hardware STM32	***/
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"



class HC05 : public Serial{
private:

	UART_HandleTypeDef* hUART = NULL;
	GPIO_TypeDef* hKeyPort = NULL;
	uint16_t keyPin;

	osThreadId taskID;

public:
	HC05(UART_HandleTypeDef* huart, GPIO_TypeDef* key_port, uint16_t key_pin);
	virtual ~HC05();

	virtual void begin();
	virtual void end();

	virtual int writeChar(char c);
	virtual int writeStr(const char* str);

	virtual char readChar();

	virtual bool isAvailable();

	UART_HandleTypeDef* getUARTInstance(){ return hUART; };


private:

	void threadTask(void const * argument);

};

#endif /* APPLICATION_USER_SERIAL_HC05_HPP_ */
