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
// �Ʒ� Source�� Buffer�� ���� �ʱ�ȭ�Ǵ� ��ó�� ��������, Base Class�� �����ڰ� ���� ȣ��Ǿ�,
// �ʱ�ȭ���� ���� buffer�� ����ϰ� ��
class PipeStream : public Stream
{
private:
	Buffer m_Buf{1024};	// Init buffer
public:
	PipeStream() : Stream(m_Buf) {}		// Bug: derived class member �� 
										// base class���� ������ ���� �� ��!
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