#include <iostream>

// 핵심 : value category 는 "expression" 의 속성입니다. 
//		  객체의 속성이 아닙니다.

// expression(표현식) : 하나의 값으로 결정되는 코드 집합.

int main()
{
	int n = 10;
	 
	n = 10;		// "n" 이라는 표현식은 lvalue

//	n + 5 = 10;  // "n+5" 이라는 표현식의 결과는 메모리가 아닌 "15"라는 값
				// 따라서 rvalue, error
	
//	n + 2 * 5 = 30; // "n + 2 * 5" 는 rvalue, error

	++n = 10;	 // ok... ++n 은 lvalue

	n++ = 20; // error.  n++은 rvalue

	int k = 3;
	int s = ++k * ++k; 
	std::cout << s << std::endl; //  25
}
// 후위형도 만들어 봅시다.
int operator++(int& n, int) // 전위형과 구별위해 사용되지 않은 2번째 인자필요
{
	int temp = n;
	n = n + 1;
	return temp;
}

// 전위형 ++을 직접 만들어 봅시다. - 물론 int 버전을 만들수 없지만..
int& operator++(int& n)
{
	n = n + 1;
	return n;
}