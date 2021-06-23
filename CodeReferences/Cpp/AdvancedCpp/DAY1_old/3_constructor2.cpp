#include <iostream>

// Base-from-Member

class Buffer
{
	char* buff;
public:
	Buffer(int size) : buff(new char[size]) 
	{
		std::cout << "버퍼 크기 " << size  << "로 초기화" << std::endl;
	}
	void useBuffer() { std::cout << "버퍼 사용" << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { buf.useBuffer();	}
};

//---------------------------------------------------------
// Stream 으로 부터 파생된 클래스를 만들고..

// 아래 코드는 버퍼가 먼저 초기화되는 것처럼 보이지만..
// 기반 클래스의 생성자가 먼저 호출되게 됩니다.
// 초기화 되지 않은 버퍼 사용하게 됨.
class PipeStream : public Stream
{
	Buffer mBuff{ 1024 }; // 버퍼 초기화
public:
	PipeStream() : Stream(mBuff) {}
	//....
};


// 위 코드를 컴파일러가 아래 처럼 변경합니다.
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




