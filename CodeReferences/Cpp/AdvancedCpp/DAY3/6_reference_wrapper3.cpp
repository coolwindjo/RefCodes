#include <iostream>
#include <functional>

void goo(int& a) { a = 100;}

// call by value를 사용하는 전달자 함수
template<typename F, typename T> void Caller(F f, T arg)
{
	f(arg);
}
int main()
{
	int n = 10;

	// Caller(goo, n); // caller 가 복사본을 만들기 때문에 실패..

	// n 을 goo에게 참조로 전달하려면
//	std::reference_wrapper<int> r(n);
//	Caller(goo, r);

	// ref(n) : reference_wrapper 객체를 생성해주는 함수.
	Caller(goo, std::ref(n) );


	std::cout << n << std::endl;
}