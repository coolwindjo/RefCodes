#include <iostream>

// 아래 Code 가 2000년도에 "modern C++ design" 책의 저자가 만든 Code입니다.
template<int N> struct int2type
{
	enum { value = N };
};

int main()
{
	foo(0);
	foo(1);	// 0, 1은 같은 Type, foo(0), foo(1) 은 같은 함수 호출

	int2type<0> t0;
	int2type<1> t1;

	foo(t0);
	foo(t1);	// t0, t1은 다른 Type, foo(t0), foo(t1) 은 다른 함수 호출
}