// 9_concept1
#include <iostream>
#include <type_traits>

// C++20 을 만들때 enable_if 를 테크닉이 아닌 "문법화" 하고 싶었습니다.
// C++11 만들때 부터 "concept" 문법 고려.

// g++ 9_concept1.cpp -std=c++20
// cl  9_concept1.cpp /std:c++latest

template<typename T>  requires std::is_pointer_v<T>
void printv(const T& v)
{
	std::cout << "포인터 인 경우" << std::endl;
}

template<typename T> requires (!std::is_pointer_v<T>)
void printv(const T& v)
{
	std::cout << "포인터가 아닌 경우" << std::endl;
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);

}
