// from 7_enable_if5.cpp
#include <iostream>
#include <type_traits>

// C++20 을 만들 때, enable_if 를 Technic이 아닌 "문법화" 하고 싶었습니다.
// C++11 만들 때 부터 "concept" 문법 고려

// g++ 	9_concept1.cpp -std=c++20
// cl	9_concept1.cpp /std=c++latest

template<typename T> requires std::is_pointer_v<T>
void printv(const T& v)
{
	std::cout << "The argument type is a pointer" << std::endl;
}

template<typename T> requires (!std::is_pointer_v<T>)
void printv(const T& v)
{
	std::cout << "The argument type is not a pointer" << std::endl;
}
int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
