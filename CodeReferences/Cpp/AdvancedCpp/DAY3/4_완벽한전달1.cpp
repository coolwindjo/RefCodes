#include <iostream>

// Perfect fowarding
// "전달 받은 인자를 다른 곳으로 완벽하게 전달하는 기술".

void foo(int a)  {}
void goo(int& a) { a = 100; }

// 함수의 수행시간을 조사하는 함수
template<typename F> void chronometry(F f, const int& arg)
{
	// 함수 호출전에 시간 측정
	f(arg); // 함수 호출
	// 걸린시간 출력
}
int main()
{
	int n = 10;

	chronometry(foo, 10); // foo(10);
	chronometry(goo, n);  // goo(n);

	std::cout << n << std::endl;
}
