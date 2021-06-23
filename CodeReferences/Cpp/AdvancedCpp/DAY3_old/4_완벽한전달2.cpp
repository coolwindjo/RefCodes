#include <iostream>


void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

// 규칙 1. 인자의 복사본이 생성되면 안된다.
// 규칙 2. rvalue 참조와 lvalue 참조 버전 2개를 제공한다.
// "아래 코드는 단 한개의 문제가 있습니다." - main 참고
template<typename F> void chronometry(F f, int& arg)
{
	f(arg);
}
template<typename F> void chronometry(F f, int&& arg)
{
	f(arg);
}
int main()
{
	hoo(10); // ok
	chronometry(hoo, 10); // 위 코드가 되므로.. 이 것도 당연히 되어야 합니다.

	int n = 10;

	chronometry(foo, 10);
	chronometry(goo, n); 

	std::cout << n << std::endl;
}
