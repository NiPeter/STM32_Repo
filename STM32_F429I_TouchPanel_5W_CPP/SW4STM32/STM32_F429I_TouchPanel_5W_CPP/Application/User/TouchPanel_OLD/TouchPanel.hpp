/*
 * TouchPanel.hpp
 *
 *  Created on: 16 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_TOUCHPANEL_OLD_TOUCHPANEL_HPP_
#define APPLICATION_USER_TOUCHPANEL_OLD_TOUCHPANEL_HPP_


#include "stm32f4xx_hal.h"


#include "adc.h"
#include "gpio.h"

#include "../TouchPanel_OLD/Filters/MedianFilter.hpp"



/********************************************************/
class Pin{

	GPIO_TypeDef*		hGPIO;
	uint16_t			PIN;

public:

	Pin(GPIO_TypeDef* hgpio, uint16_t pin):hGPIO(hgpio),PIN(pin){};
	Pin(Pin &pin){ hGPIO = pin.hGPIO; PIN = pin.PIN;};

	void Write(bool state){ HAL_GPIO_WritePin(hGPIO,PIN,(GPIO_PinState)state); };
	void Toggle(void){ HAL_GPIO_TogglePin(hGPIO,PIN); };
	bool Read(void){ return HAL_GPIO_ReadPin(hGPIO,PIN); };

};
/********************************************************/



/********************************************************/
class TouchPanel{

/***	Static variables	***/
	static const uint32_t	SettlingTime_ms = 1; // with 1.8kOhm between ADC and GND =  0.3ms
	static const uint32_t 	BufferSize 		= 6;
	public: static const uint16_t	Treshold		= 3000;

/***	Hardware objects	***/
	ADC_HandleTypeDef*	hADC;
	Pin		UpperLeft;
	Pin		UpperRight;
	Pin		LowerLeft;
	Pin		LowerRight;

/***	Variables  	***/

	uint16_t Data[BufferSize];
	IFilter<float,float> *FilterT, *FilterX, *FilterY;
public:

	float X;
	float Y;
	bool Touched;

public:

	TouchPanel( ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t upR, uint16_t upL, uint16_t loR, uint16_t loL);
	TouchPanel( ADC_HandleTypeDef* hadc, Pin upR, Pin upL, Pin loR, Pin loL);

	ADC_TypeDef* GetADCInstance(void);
	bool IsTouched( void ) {return Touched;};
	float GetX(void){return X;};
	float GetY(void){return Y;};

	void Process(void);

//private:

	void FilterInit(void);

	bool CheckTouch(void);
	float CheckX(void);
	float CheckY(void);

	void Measure(void);
	void SetHighPolar(void);
	void SetXPolar(void);
	void SetYPolar(void);

	float Average( const uint16_t data[], uint16_t size);

	inline uint32_t GetADCValue(){return HAL_ADC_GetValue(hADC);};

};
/********************************************************/

#endif /* APPLICATION_USER_TOUCHPANEL_OLD_TOUCHPANEL_HPP_ */
