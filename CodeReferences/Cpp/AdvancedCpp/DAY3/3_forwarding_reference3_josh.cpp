#include "cppmaster.h"	//vc, g++ 모두 사용가능
// #include <iostream>

template<typename T> void foo(T&& arg)
{
	LOG_FUNCTION_NAME();

	// __FUNCTION__: 함수 이름을 담은 MACRO. C++ 표준
	// std::cout<< __FUNCTION__ <<std::endl;

	// __FUNCSIG__: 함수 Sinature를 모두 출력. VC 전용 g++ 안됨
	// std::cout<< __FUNCSIG__ <<std::endl;

	// __PRETTY_FUNCTION__: 함수 Sinature를 모두 출력. g++ 전용
	// std::cout<< __PRETTY_FUNCTION__ <<std::endl;
}

int main()
{
	int n = 10;

	foo(n);  	// foo(int&) 	함수 생성
	foo(10); 	// foo(int&&)	함수 생성

	const int c = 10;
	foo(c); 
}




