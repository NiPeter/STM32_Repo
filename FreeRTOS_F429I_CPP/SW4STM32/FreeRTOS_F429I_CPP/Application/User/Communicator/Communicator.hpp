/*
 * Communicator.hpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_
#define APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_

#include "Command.hpp"
#include "Serial.hpp"

class Communicator
{
	Serial* SerialPort;
public:
	Communicator(Serial* serial);
	~Communicator();

	Command receiveCmd();
	void sendCmd(Command cmd);

private:
	Command unpackMsg(const char* msg);
	char*  packMsg(Command cmd, char * msg);

	CmdType_e cmdTypeFromMsg(const char* msg);
	float paramFromMsg(const char* msg);
};


#endif /* APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_ */
