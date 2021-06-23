#include <iostream>

// Base-from-Member

class Buffer
{
	char* buff;
public:
	Buffer(int size) : buff(new char[size])
	{
		std::cout << "버퍼 크기 " << size << "로 초기화" << std::endl;
	}
	void useBuffer() { std::cout << "버퍼 사용" << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { buf.useBuffer(); }
};

//---------------------------------------------------------
// Stream 으로 부터 파생된 클래스를 만들고..

// 핵심 원리 : 버퍼만을 위한 기반클래스를 설계해라

// "Base From Member" 라는 이름을 가진 기술

// 기반 클래스로 보내고 싶은 멤버 데이타가 있으면..
// 멤버 데이타 만을 위한 별도의 기반 클래스를 설계 하라.

// google.com  "C++ Idioms" 검색후.. 1번째 링크.

class BaseBuffer
{
protected:
	Buffer mBuff{ 1024 }; // 버퍼 초기화
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




