/*
 * Serial.hpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_SERIAL_SERIAL_HPP_
#define APPLICATION_USER_SERIAL_SERIAL_HPP_

/***	SERIAL INTERFACE	***/
class Serial{

public:
	Serial();
	virtual ~Serial();

	virtual void begin();
	virtual void end();

	virtual int writeChar(char c);
	virtual int writeStr(const char* str);

	virtual char readChar();

	virtual bool isAvailable();

};


#endif /* APPLICATION_USER_SERIAL_SERIAL_HPP_ */
