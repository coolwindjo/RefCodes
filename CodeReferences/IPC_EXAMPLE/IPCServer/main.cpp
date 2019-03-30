#include <stdio.h>
#include "IPCServer.h"

void main(int argc, char** argv)
{
	CIPCServer* poIPCServer;
	poIPCServer = new CIPCServer(PIPE_NAME, 10);
	
	for (size_t i = 0; i < 10; i++)
	{
		char message[10] = "message\r\n";
		int32_t s32Size = 10;
		uint8_t result = poIPCServer->u8Write(s32Size, message, 10);

		Sleep(100);
	}

}