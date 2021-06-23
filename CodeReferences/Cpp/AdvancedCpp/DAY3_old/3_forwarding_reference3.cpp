#include "cppmaster.h" // vc, g++ 모두 사용가능
//#include <iostream>

template<typename T> void foo(T&& arg)
{
	LOG_FUNCTION_NAME();	// 아래 매크로 사용해서 출력

	// __FUNCTION__ : 함수이름을 담은 매크로.  C++ 표준
	// __FUNCSIG__ : 함수 시그니쳐를 모두 출력 .  VC 전용  g++ 안됨.
	// __PRETTY_FUNCTION__ : g++ 전용.


	//std::cout << __FUNCTION__ << std::endl;

	//std::cout << __FUNCSIG__ << std::endl;
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
	int n = 10;

	foo(n);  // foo(int&)  함수 생성
	foo(10); // foo(int&&) 함수 생성

	const int c = 10;
	foo(c); 
}




