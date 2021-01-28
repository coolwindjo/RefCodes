#include <iostream>

// [[nodiscard]] : 함수 반환값을 받지 않은 경우 경고를 내어 달라는 의미.. - C++17 부터
// [[nodiscard("message")]]  : C++20

[[nodiscard]] int* Alloc(std::size_t sz)
{
	return new int[10];
}

enum [[nodiscard]] ERRORCODE { WARNING, CRITICAL, FATAL };

ERRORCODE goo() { return FATAL; }

//[[알수없는명령]] : 컴파일 시에 무시..(경고)
[[clksajcfalsdajlskdl]]  void hoo() {}

int main()   
{
	goo();

	// 아래 코드의 문제점은 ?
	// 리턴값을 무시하면 안되는데.. 무시하고 있다..
	//Alloc(100);
}