#include <iostream>
#include <type_traits>

// Template 인자 T에 대한 다양한 속성을 조사하는 기술 - "type traits" 라고 합니다.
template<typename T> void printv(const T& v)
{
	// if ( T가 Pointer Type 이면,)
	// if (std::is_pointer_v<T>)
	// {
	// 	// 이 Code가 Error 인 이유는 T가 int 일 때, "*v" 를 사용할 수 없습니다.
	// 	std::cout << v << ":" << *v << std::endl;
	// }
	// else
	// {
	// 	std::cout << v << std::endl;
	// }
	
	// C++17 의 새로운 if문을 사용하면
	// type이 조건을 만족하지 않을 때 "C++ code 생성"을 하지 않도록 할 수 있습니다.
	if constexpr (std::is_pointer_v<T>)
	{
		std::cout << v << ":" << *v << std::endl;
	}
	else
	{
		std::cout << v << std::endl;
	}
}
// Template 만들 때, 조건에 따라 다른 구현을 제공하는 방법
// 1. integral_constant - C++11
// 2. enable_if			- C++11: C++20 전까지는 최고!
// 3. if constexpr		- C++17
// 4. concept 기술		- C++20: enable_if 의 발전된 형태!	C++의 혁명!

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
