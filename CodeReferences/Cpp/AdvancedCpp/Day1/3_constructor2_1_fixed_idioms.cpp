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
// �ٽ� 1. Buffer���� ���� Base class�� �����϶�!
// "Base-From-Member" ��� �̸��� ���� ���
// Base class�� ������ ���� Member attribute�� ������,
// Member attribute���� ���� ������ Base class�� ���� �϶�!

// google�� "C++ Idioms" �˻�... 1 ��° �׸�
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