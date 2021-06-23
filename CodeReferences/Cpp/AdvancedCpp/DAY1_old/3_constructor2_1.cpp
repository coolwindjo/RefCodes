#include <iostream>

// Base-from-Member

class Buffer
{
	char* buff;
public:
	Buffer(int size) : buff(new char[size])
	{
		std::cout << "���� ũ�� " << size << "�� �ʱ�ȭ" << std::endl;
	}
	void useBuffer() { std::cout << "���� ���" << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { buf.useBuffer(); }
};

//---------------------------------------------------------
// Stream ���� ���� �Ļ��� Ŭ������ �����..

// �ٽ� ���� : ���۸��� ���� ���Ŭ������ �����ض�

// "Base From Member" ��� �̸��� ���� ���

// ��� Ŭ������ ������ ���� ��� ����Ÿ�� ������..
// ��� ����Ÿ ���� ���� ������ ��� Ŭ������ ���� �϶�.

// google.com  "C++ Idioms" �˻���.. 1��° ��ũ.

class BaseBuffer
{
protected:
	Buffer mBuff{ 1024 }; // ���� �ʱ�ȭ
};

class PipeStream : public BaseBuffer, public Stream
{
public:
	PipeStream() : Stream(mBuff) {}
	//....
};


int main()
{
	PipeStream ps;
}




