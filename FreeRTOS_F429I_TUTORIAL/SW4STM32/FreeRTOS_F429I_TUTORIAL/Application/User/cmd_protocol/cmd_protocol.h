/*
 * cmd_protocol.h
 *
 *  Created on: 25 maj 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_CMD_PROTOCOL_CMD_PROTOCOL_H_
#define APPLICATION_USER_CMD_PROTOCOL_CMD_PROTOCOL_H_

#define CP_LIST_SIZE		10
#define CP_MSG_SIZE			30

#include "cmd_commands.h"

typedef enum
{
  CP_OK       		= 0x00U,
  CP_ERROR    		= 0x01U,
  CP_TIMEOUT  		= 0x03U,
  CP_MSG_READY 		= 0x04U,
  CP_MSG_NOT_READY 	= 0x05U,
} CP_StatusTypeDef;

typedef struct{
	Command_Enum Command;
	float	Param;
} Command_TypeDef;


typedef struct{
	Command_TypeDef CmdBuff[CP_LIST_SIZE];
	int Cnt;
} CommandList_TypeDef;



CP_StatusTypeDef CP_UnpackMsg(const char* msg,CommandList_TypeDef * cmdL);

CP_StatusTypeDef CP_PackMsg(Command_TypeDef cmd, char* msg);

CP_StatusTypeDef CP_ComposeMsg(char byte, char result[] );

void CP_ExecuteCommands(CommandList_TypeDef * cmdL);



#endif /* APPLICATION_USER_CMD_PROTOCOL_CMD_PROTOCOL_H_ */
