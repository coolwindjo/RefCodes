#include <iostream>

void foo(int a)  {}
void goo(int& a) { a = 100; }

// 함수의 수행시간을 조사하는 함수
template<typename F> void chronometry(F f,int arg)
{
	// 함수 호출 전에 시간 측정
	f(arg);	// 함수 호출
	// 걸린시간 출력
}
int main()
{
	int n = 10;

	chronometry(foo, 10); 	// foo(10);
	chronometry(goo, n); 	// goo(n);

	std::cout << n << std::endl;
}
