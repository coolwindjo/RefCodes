#include <iostream>

// Base-from-Member

class Buffer
{
	char* buff;
public:
	Buffer(int size) : buff(new char[size]) 
	{
		std::cout << "���� ũ�� " << size  << "�� �ʱ�ȭ" << std::endl;
	}
	void useBuffer() { std::cout << "���� ���" << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { buf.useBuffer();	}
};

//---------------------------------------------------------
// Stream ���� ���� �Ļ��� Ŭ������ �����..

// �Ʒ� �ڵ�� ���۰� ���� �ʱ�ȭ�Ǵ� ��ó�� ��������..
// ��� Ŭ������ �����ڰ� ���� ȣ��ǰ� �˴ϴ�.
// �ʱ�ȭ ���� ���� ���� ����ϰ� ��.
class PipeStream : public Stream
{
	Buffer mBuff{ 1024 }; // ���� �ʱ�ȭ
public:
	PipeStream() : Stream(mBuff) {}
	//....
};


// �� �ڵ带 �����Ϸ��� �Ʒ� ó�� �����մϴ�.
/*
class PipeStream : public Stream
{
	Buffer mBuff;
public:
	PipeStream() : Stream(mBuff), mBuff{ 1024 } {}
	//....
};
*/


int main()
{
	PipeStream ps;

//	Buffer buff(1024);
//	Stream stream(buff);
}




