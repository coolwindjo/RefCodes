// #include "cppmaster.h"
#include <iostream>

// 핵심: value category는 "expression" 의 속성입니다.
//			객체의 속성이 아님!
// expression(표현식): 하나의 값으로 결정되는 Code 집합

int main()
{
	int n = 10;
	 
	n = 10;			// "n" 이라는 expression은 lvalue
	// n + 5 = 10; 	// "n+5" 이라는 expression의 결과는 Memory가 아닌 "15"라는 값
					// 따라서, rvalue, Error!
	// n + 2 * 5 = 30;	// "n+2*5"는 rvalue, Error! 

	++n = 10;		// OK. ++n은 lvalue

	int k = 3;
	int s = ++k * ++k;
	std::cout<< s <<std::endl;	// 25

}

// 전위형 ++를 직접 만들어 봅시다. (물론, int version을 만들 수는 없음)
int& operator++(int& n)
{
	n = n + 1;
	return n;
}
// 후위형 ++도 만들어 봅시다.
int operator++(int& n, int)	// 전위형과 구별위해 사용되지 않는 2번째 인자 필요
{
	int temp = n;
	n = n + 1;
	return temp;
}