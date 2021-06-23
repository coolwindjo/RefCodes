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
// 핵심 1. Buffer만을 위한 Base class를 설계하라!
// "Base-From-Member" 라는 이름을 가진 기술
// Base class로 보내고 싶은 Member attribute가 있으면,
// Member attribute만을 위한 별도의 Base class를 설계 하라!

// google에 "C++ Idioms" 검색... 1 번째 항목
// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
class BaseBuffer
{
protected:
	Buffer m_buf { 1024 };	// Init buffer
};

class PipeStream : protected BaseBuffer, public Stream
{
public:
	PipeStream() : Stream(m_buf) {}
};

int main()
{
	PipeStream ps;
}