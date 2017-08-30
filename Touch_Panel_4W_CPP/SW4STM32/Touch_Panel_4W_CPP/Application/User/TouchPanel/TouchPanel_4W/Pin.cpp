/*
 * Pin.cpp
 *
 *  Created on: 29 sie 2017
 *      Author: Peter
 */

#include "Pin.hpp"


Pin::Pin(GPIO_TypeDef* hgpio, uint16_t pin):hGPIO(hgpio),nPIN(pin){ SetInputMode(); };
Pin::Pin(Pin &pin){ hGPIO = pin.hGPIO; nPIN = pin.nPIN; SetInputMode(); };

void Pin::Write(bool state){ HAL_GPIO_WritePin(hGPIO,nPIN,(GPIO_PinState)state); };
void Pin::Toggle(void){ HAL_GPIO_TogglePin(hGPIO,nPIN); };
bool Pin::Read(void){ return HAL_GPIO_ReadPin(hGPIO,nPIN); };

void Pin::SetOutputMode( PullUp_e pull ) {
	//if(Mode == Output) return;

	HAL_GPIO_DeInit(hGPIO, nPIN);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = nPIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(hGPIO, &GPIO_InitStruct);

	Mode = Output;
};

void Pin::SetInputMode( PullUp_e pull ) {
	//if(Mode == Input) return;

	HAL_GPIO_DeInit(hGPIO, nPIN);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = nPIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(hGPIO, &GPIO_InitStruct);

	Mode = Input;
};

AnalogPin::AnalogPin(ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t pin):Pin(hgpio,pin),hADC(hadc){
	Mode = None;
	SetAnalogMode();
};

void AnalogPin::SetAnalogMode(void) {
	//if(Mode == Analog) return;

	HAL_GPIO_DeInit(hGPIO, nPIN);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = nPIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(hGPIO, &GPIO_InitStruct);

	Mode = Analog;
};

ADC_HandleTypeDef* AnalogPin::GetADC_Handle(void){
	return hADC;
}

void AnalogPin::Measure_IT(void){
	if(Mode != Analog) SetAnalogMode();
	HAL_ADC_Start_IT(hADC);
}

void AnalogPin::Measure(void){
	if(Mode != Analog) SetAnalogMode();
	HAL_ADC_Start(hADC);
}

uint32_t AnalogPin::GetADCValue(void){ return HAL_ADC_GetValue(hADC);};




