/*
 * cmd_commands.h
 *
 *  Created on: 6 cze 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_CMD_PROTOCOL_CMD_COMMANDS_H_
#define APPLICATION_USER_CMD_PROTOCOL_CMD_COMMANDS_H_

typedef enum {Empty = 0,

	// SET
	//Platform position and orientation X Y Z A B C
	setX = 10 , setY, setZ, setRoll, setPitch, setYaw ,
	setMode,setAmp,setDiw,

	// GET
	getX = 127, getY, getZ, getRoll, getPitch, getYaw ,
	getZmienna,


} Command_Enum;

#endif /* APPLICATION_USER_CMD_PROTOCOL_CMD_COMMANDS_H_ */
