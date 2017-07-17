/*
Execute * cmd_protocol.c
 *
 *  Created on: 25 maj 2017
 *      Author: Peter
 */

#include "stm32f4xx_hal.h"
#include "cmd_protocol.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"



CP_StatusTypeDef CP_UnpackMsg(const char* msg,CommandList_TypeDef * cmdL){

	if(cmdL == NULL) {

		return CP_ERROR;
	}

	char msg_buff[CP_MSG_SIZE]={0};
	int cmd_e;
	char * token;

	cmdL->Cnt=0;

	strcpy(msg_buff,msg); // wykonaj kopie wiadomosci

	/* get the first token */
	token = strtok(msg_buff, ";");

	/* walk through other tokens */
	while( token != NULL )
	{
		//if(*token == '\n') break; // je¿eli znak \n to koniec while

		cmd_e = strcspn(token, "=");
		cmdL->CmdBuff[cmdL->Cnt].Command = atoi(token);

		if(strlen(token) > cmd_e+1){ // je¿eli jest coœ za znakiem = to...
			token += cmd_e+1; // przesuñ wskaŸnik na parametr

			int p_n;
			int p_d;

			p_n = atoi(token); // pobierz wartoœæ ca³kowit¹

			token+=strcspn(token, "."); // szukaj kropki i  przesuñ na ni¹ wskaŸnik
			if(*token!='\0'){	// je¿eli wskaŸnik NIE wskazuje koniec stringa

				token++;	// przesuñ wskaŸnik na wartoœæ nieca³kowit¹
				p_d = atoi(token); // pobierz wartoœæ u³amkow¹
				cmdL->CmdBuff[cmdL->Cnt].Param = p_n+p_d/pow(10.0,strlen(token)); // oblicz parametr jako float

			}else cmdL->CmdBuff[cmdL->Cnt].Param = p_n; // je¿eli nie ma wartoœci po . to parametr jest ca³kowity, zapisz go

		}else cmdL->CmdBuff[cmdL->Cnt].Param = 0; // Nie ma nic za znakiem =

		cmdL->Cnt++;
		token = strtok(NULL, ";"); // Nastepna komenda
	}
	return CP_OK;
}

CP_StatusTypeDef CP_PackMsg(Command_TypeDef cmd, char* msg){

	uint16_t iParam1 = (uint16_t)cmd.Param;
    uint16_t iParam2 = (uint16_t)((cmd.Param - iParam1)*1000.0);

    sprintf(msg,"%i=%i.%i;\r\n",(uint16_t)cmd.Command, iParam1, iParam2);

	return CP_OK;
}

CP_StatusTypeDef CP_ComposeMsg(char byte, char result[] ){

	static uint8_t bt_index = 0;
	static char data_buffer[CP_MSG_SIZE];

	if(byte == '\n'){
		// Terminate string with null character
		data_buffer[bt_index] = '\0';

		// Copy string from data buffer to result
		strcpy(result,data_buffer);

		//Clean before next transition
		//BT_MsgClear(data_buffer);
		bt_index = 0;

		return CP_MSG_READY;
	}

	if(byte != '\r'){
		//Receive byte and save it to data_buffer
		data_buffer[bt_index] = byte;

		// Check msg size
		if(++bt_index==CP_MSG_SIZE){
			bt_index =0;
			return CP_ERROR;
		}
	}
	return CP_MSG_NOT_READY;

}


void CP_ExecuteCommands(CommandList_TypeDef * cmdL){

	int cmdIndex = 0;
	Command_TypeDef *cmd;

	while(cmdL->Cnt--){

		cmd = &cmdL->CmdBuff[cmdIndex];

		switch(cmd->Command){

		default:
			break;
		}

		cmdIndex++;
	}

}

