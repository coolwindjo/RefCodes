#include <iostream>

// Base-from-Member

class Buffer
{
	char* buff;
public:
	Buffer(int size) : buff(new char[size]) 
	{
		std::cout << "Initialize the buffer (size: " << size << ")"  << std::endl;
	}
	void useBuffer() { std::cout << "Using buffer..." << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { buf.useBuffer();	}
};

// /*/-----------------------------------------------
// 아래 Source는 Buffer가 먼저 초기화되는 것처럼 보이지만, Base Class의 생성자가 먼저 호출되어,
// 초기화되지 않은 buffer를 사용하게 됨
class PipeStream : public Stream
{
private:
	Buffer m_Buf{1024};	// Init buffer
public:
	PipeStream() : Stream(m_Buf) {}		// Bug: derived class member 를 
										// base class에서 쓰도록 하지 말 것!
};
// This is compiled as...
/*/
class PipeStream : public Stream
{
private:
	Buffer m_Buf;
public:
	PipeStream() : Stream(m_Buf), m_Buf(1024) {}
};
//*/

int main()
{
	/*/
	Buffer buff(1024);
	Stream stream(buff);
	/*/
	PipeStream ps;
	//*/
}