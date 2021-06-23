// 1_rvalue3
#include <iostream>

// value category 와 decltype
int main()
{
	int n = 0;
	int* p = &n;

	// 규칙 1. () 안에 심볼만 있을때 : 해당 심볼의 선언을 보고 타입 결정
	decltype(n) d1;	// int  d1
	decltype(p) d2;	// int* d2

	// 규칙 2. () 안에 심볼+연산자 등의 표현식이 있을때
	//			해당 표현식이 lvalue 가 될수 있으면 참조,, 아니면 값.
	decltype(*p)  d3; // int& d3;  초기값이 없어서 error
	decltype((n)) d4; // int& d4; 
	decltype(n+n) d5; // int  d5;
	decltype(++n) d6; // int& d6

	
	int x[3] = { 1,2,3 };
	
	decltype( x[0] ) d7; // x[0] = 10 이 된다... 따라서
						// int& d7
	
	// x[0] 의 타입은 분명 "int&" 입니다.
	// 그런데, auto가 우변과 완벽히 동일한 타입으로 결정하면 오히려 불편합니다
	// 그래서, 우변의 "참조, const, volatile" 속성을 버리고 타입결정.
	auto a1 = x[0];

	const int c = 10;
	auto a2 = c; // a2의 타입은 ?
	a2 = 20; // ok..  
}


