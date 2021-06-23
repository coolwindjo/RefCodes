#include <iostream>

// (함수템플릿에서 T가 결정된후)
// 치환에 실패 한것은 에러가 아니다.

// Substitution Failure Is Not An Error => "SFINAE"

// C++11 이 아닌 예전 부터 사용되던 용어.

template<typename T>
typename T::type  foo(T a)  { std::cout << "T" << std::endl; return 0; }

// typename int::type foo(int a) { .... } 인 함수를 생성하려고 한다.

void foo(...) { std::cout << "..." << std::endl; }

int main()
{
	// 어느 함수를 사용할지는 "함수인자"를 보고 결정
	foo(3);  // 1. foo 템플릿을 사용하기로 결정
			 //    => 그런데.. 함수를 만드는 데.. 실패.!!! 
			//	   => 에러가 아니라.. 그냥.. foo(int)를 못만든것.!!
			//	   => foo(...) 버전 사용가능..
}