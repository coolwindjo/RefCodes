#pragma once
#include <Windows.h>
#include "CTypedefs.h"

#define BUFFER_SIZE	512
#define PIPE_NAME	"\\\\.\\pipe\\PIPE_ADDRESS"

typedef struct {
	float32_t f32Dummy1;
	float32_t f32Dummy2;
} Test_t;

class CIPCServer
{
public:
	CIPCServer(const char* pcPipeName,
		const int32_t s32MaxInstances,
		SECURITY_ATTRIBUTES* pstSecurityAttributes = nullptr);
	~CIPCServer();

	uint8_t u8Accept();
	uint8_t u8Read(int32_t& s32ReadedBytes,
		void* pvReadBuffer,
		const int32_t s32ReadBufferSize);
	uint8_t u8Write(int32_t& s32WrittenBytes,
		void* pvWrittenData,
		const int32_t s32WriteDataSize);
	uint8_t u8Verify();
	void vDisconnect();
	HANDLE& native_object();

	uint8_t u8Connected;
private:
	void* m_pvNamedPipe;
	int32_t m_s32MaxInstances;

};

