// from 5_integral_constant1.cpp
#include <iostream>
#include <type_traits>

// // Pointer인 경우와, 
// template<typename T> void printv_pointer(const T& v)
// {
// 	std::cout << v << ":" << *v << std::endl;	// 그래도 Error 남!
// }

// // Pointer가 아닌 경우로 분리
// template<typename T> void printv_not_pointer(const T& v)
// {
// 	std::cout << v << std::endl;
// }
// template<typename T> void printv(const T& v)
// {
// 	if (std::is_pointer_v<T>)
// 	{
// 		printv_pointer(v);
// 	}
// 	else
// 	{
// 		printv_not_pointer(v);
// 	}
// }

// printv 를 만드는 4가지 기술
// 1. integral_constant => printv_imp( v, std::is_pointer<T>() )
// 2. enable_if 기술 => 아래 Code
// 		C++11에 표준에 추가되었지만, 그 전에도 만들어서 사용하면 됨
//		SFINAE 는 C++11이 아닌 C++ 처음부터 있던 개념
// 3. if constexpr (std::is_pointer_v<T>) - C++17
// 5. concept - c++20

// github.com/aosp-mirror
// platform_system_core
// libutils/include/utils/typeHelpes.h
// copy_type()

template<typename T>
// std::enable_if_t<조건, ReturnType>
std::enable_if_t< std::is_pointer_v<T> >
printv(const T& v)
{
	// std::cout << v << ":" << *v << std::endl;
	std::cout << "The argument type is a pointer" << std::endl;
}

template<typename T>
std::enable_if_t< !std::is_pointer_v<T> >
printv(const T& v)
{
	std::cout << v << std::endl;
	std::cout << "The argument type is not a pointer" << std::endl;
}
int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
