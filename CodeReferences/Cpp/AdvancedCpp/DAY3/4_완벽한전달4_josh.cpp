#include <iostream>

void foo(int a)  {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

// "T&&" 를 사용하면 아래 2개의 함수를 자동 생성할 수 있다.
// 그런데, 문제는 2개 함수의 구현이 같아야 한다.

// template<typename F> void chronometry(F f, int& arg)
// {
// 	// f(arg);
// 	f( static_cast<int&>(arg) );	// 필요 없는 Casting 이지만...
// 									// 있어도 문제 되지 않는 Code
// }

// template<typename F> void chronometry(F f, int&& arg)
// {
// 	f( static_cast<int&&>(arg) );
// }

// 아래 함수가 결국 위 2개의 함수를 자동 생성합니다.
template<typename F, typename T> void chronometry(F f, T&& arg)
{
	// 아래 Cating은
	// "lvalue는 (인자로 오면,) lvalue로 Casting하고,"
	// "rvalue는 (인자로 오면,) rvalue로 Casting한다."
	// f( static_cast<T&&>(arg) );

	f( std::forward<T>(arg) );	// std::forward 함수가 위처럼 Casting하는 역할을 합니다.
								// 다른 곳에 인자를 전달 할 때, 사용한다는 의미로 
								// "forward" 라는 keyword 사용
}

// 핵심 결론! 완벽한 전달을 하려면,
// 1. 인자를 T&&로 받으세요.
// 2. 인자를 다른 곳에 보낼때는 std::forward<T>(arg) 로 묶어서 보내세요.

int main()
{
	int n = 10;
	chronometry(foo, 10);	// T: int,	T&&: int&& 		Casting: static_cast<int&&>(arg)
	chronometry(goo, n);	// T: int&, T&&: int& && 	Casting: static_cast<int&>(arg)

	return 0;
}
