
#include "TouchPanel_4W.hpp"

TouchPanel4W::TouchPanel4W(AnalogPin &x_analog,Pin &x_gnd,AnalogPin &y_analog,Pin &y_gnd)
:XAnalog(x_analog),YAnalog(y_analog),XGnd(x_gnd),YGnd(y_gnd){
	X = 0;
	Y = 0;
	Touched = false;
	InitFilters();
}

/**
 * @brief Initialise TouchPanel filters
 */
void TouchPanel4W::InitFilters(){ //TODO User shoud be able to attach own IFilter!!
	XFilter = new MedianFilter(15,5);
	YFilter = new MedianFilter(15,5);
}
/********************************************************/



/**
 * @brief Process function
 * @note Should be called periodicaly!
 */
void TouchPanel4W::Process(void){

	PrepareTouchDetection();
	osDelay(settlingTimeMs);
	if(XAnalog.Read() != false){
		XFilter->Reset();
		YFilter->Reset();
		Touched = false;
		return;
	}

	float tmpX = XFilter->Filter(MeasureX());
	float tmpY = YFilter->Filter(MeasureY());

	taskENTER_CRITICAL();{
		if(tmpX && tmpY){
		X= tmpX;
		Y= tmpY;
		Touched = true;
		}
	}taskEXIT_CRITICAL();

}
/********************************************************/



/**
 * @brief Conversion Complete Callback,
 * @note Should be called in ADC interrupt!
 * @param hadc
 */
void TouchPanel4W::ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc){

}
/********************************************************/






/********************************************************/
/********************************************************/

uint32_t TouchPanel4W::MeasureX(){
	PrepareXMeasurement();
	osDelay(settlingTimeMs);
	YAnalog.Measure();
	HAL_ADC_PollForConversion(YAnalog.GetADC_Handle(),100);
	return YAnalog.GetADCValue();

}
uint32_t TouchPanel4W::MeasureY(){
	PrepareYMeasurement();
	osDelay(settlingTimeMs);
	XAnalog.Measure();
	HAL_ADC_PollForConversion(XAnalog.GetADC_Handle(),100);
	return XAnalog.GetADCValue();

}

/**
 * @details Function prepares pins to measurement.
 * @param analog
 * @param vcc
 * @param gnd
 * @param hiZ
 */
/********************************************************/
void TouchPanel4W::PrepareMeasurement(AnalogPin &analog, Pin &vcc, Pin &gnd, Pin &hiZ){
	analog.SetAnalogMode();

	hiZ.SetInputMode();

	vcc.SetOutputMode();
	vcc.Write(true);

	gnd.SetOutputMode();
	gnd.Write(false);
}

void TouchPanel4W::PrepareXMeasurement(){
	PrepareMeasurement(YAnalog,XAnalog,XGnd,YGnd);
}
void TouchPanel4W::PrepareYMeasurement(){
	PrepareMeasurement(XAnalog,YAnalog,YGnd,XGnd);
}

void TouchPanel4W::PrepareTouchDetection(){
	XAnalog.SetInputMode(PullUp);
	YGnd.SetOutputMode(PullDown);

	YAnalog.SetInputMode();
	XGnd.SetInputMode();
}
/********************************************************/
