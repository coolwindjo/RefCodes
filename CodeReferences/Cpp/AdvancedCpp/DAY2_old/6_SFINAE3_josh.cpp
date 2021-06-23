#include <iostream>

// SFINAE 가 적용되는 곳
// 1. Return type
// 2. 함수 인자
// 3. Template 인자

// template<typename T> typename T::type foo(T a)
// template<typename T> void foo(T a, typename T::type* p = 0)
// template<typename T, typename T::type* p = 0> void foo(T a)

template<typename T> void foo(T a)
{
	typename T::type n;	// 1. SFINAE 에 의해 ... Version 실행
						// 2. Compile Error
	std::cout << "T" << std::endl;
}
// int::type foo(int a) {....}

void foo(...) { std::cout << "..." << std::endl; }

int main()
{
	foo(3); 
}