#include <iostream>

int& foo(int a, int b, int& c) 
{
	c = 200; 
	return c; 
}

// 완벽한 전달은 대부분 "가변인자 템플릿" 기술을 사용합니다.
template<typename F, typename ... T> 
// auto chronometry(F f, T&& ... arg)  // 반환 타입이 참조인 경우 참조를 제거한 타입으로 추론
// auto chronometry(F f, T&& ... arg) -> decltype( f(std::forward<T>(arg)...) )
decltype(auto) chronometry(F f, T&& ... arg)
{
	return f(std::forward<T>(arg)... ); 
}

int main()
{
	int n = 10;

	int& ret = chronometry(foo, 10, 20, n); 

	std::cout << n << std::endl;
}
