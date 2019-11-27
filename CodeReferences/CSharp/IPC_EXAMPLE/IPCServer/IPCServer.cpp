#include "IPCServer.h"


CIPCServer::CIPCServer(const char*		pcPipeName,
	const int32_t	s32MaxInstances,
	SECURITY_ATTRIBUTES* pstSecurityAttributes) :
	m_pvNamedPipe(INVALID_HANDLE_VALUE),
	m_s32MaxInstances(s32MaxInstances)
{

	do {
		if (pcPipeName == nullptr || s32MaxInstances <= 0) {
			break;
		}

		m_pvNamedPipe = ::CreateNamedPipe(
			pcPipeName,
			(PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED),
			(PIPE_TYPE_BYTE | PIPE_NOWAIT),
			static_cast<DWORD>(s32MaxInstances), // max pipe instances < 255
			0, 0, 0,
			pstSecurityAttributes
		);

		u8Connected = 0;
		if (m_pvNamedPipe == INVALID_HANDLE_VALUE) {
			break;
		}

	} while (false);

}

CIPCServer::~CIPCServer()
{
	vDisconnect();
}

uint8_t CIPCServer::u8Accept()
{
	uint8_t u8Result = 0;

	do
	{
		// Wait for the client to connect; if it succeeds, the function returns a nonzero value.
		// If the function returns zero, GetLastError returns ERROR_PIPE_CONNECTED.
		BOOL stConnected = ::ConnectNamedPipe(m_pvNamedPipe, nullptr);

		if (!(stConnected ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED))) {
			break;
		}

		u8Result = 1;
		u8Connected = 1;
	} while (false);

	return u8Result;
}

uint8_t CIPCServer::u8Read(int32_t& s32ReadedBytes,
	void* pvReadBuffer,
	const int32_t s32ReadBufferSize)
{
	uint8_t u8Result = 0;
	DWORD stRealBytesRead = 0;

	//do
	//{
	if (!ReadFile(m_pvNamedPipe,
		pvReadBuffer,
		static_cast<DWORD>(s32ReadBufferSize),
		&stRealBytesRead,
		nullptr))
	{
		//break;
		return 0;
	}

	if (stRealBytesRead == 0)
	{
		return 0;
		//break;
	}

	s32ReadedBytes = stRealBytesRead;
	u8Result = 1;
	//} while (false);

	return u8Result;
}

uint8_t CIPCServer::u8Write(int32_t& s32WrittenBytes,
	void* pvWrittenData,
	const int32_t s32WriteDataSize)
{

	uint8_t u8Result = 0;
	DWORD stRealBytesWritten = 0;

	do
	{
		if (!WriteFile(m_pvNamedPipe,
			pvWrittenData,
			static_cast<DWORD>(s32WriteDataSize),
			&stRealBytesWritten,
			nullptr))
		{
			break;
		}

		if (s32WriteDataSize != stRealBytesWritten)
		{
			break;
		}

		s32WrittenBytes = stRealBytesWritten;
		u8Result = 1;
	} while (false);

	return u8Result;
}

uint8_t CIPCServer::u8Verify()
{
	return m_pvNamedPipe != INVALID_HANDLE_VALUE;
}

void CIPCServer::vDisconnect()
{
	if (m_pvNamedPipe != INVALID_HANDLE_VALUE)
	{
		// flush the pipe to allow the client to read the pipe's contents before disconnecting.
		// then disconnect the pipe, and close the handle to this pipe instance.
		::FlushFileBuffers(m_pvNamedPipe);
		::DisconnectNamedPipe(m_pvNamedPipe);
		::CloseHandle(m_pvNamedPipe);
	}
}

HANDLE& CIPCServer::native_object()
{
	return m_pvNamedPipe;
}