// 9_concept4.cpp
#include <iostream>
#include <type_traits>

// std::is_integral_v<T> : type_tratis, 타입 속성 조사, 템플릿 부분 특수화 문법사용
// integral              : concept 문법. 타입이 가져야 되는 조건을 명시.
//							보다 많은 조건을 만족하는 함수가 선택됨
template<typename T> 
concept integral = std::is_integral_v<T>;

//template<typename T> requires std::is_integral_v<T>
template<typename T> requires integral<T>  // && 조건2<T>
void foo(T a) {}

int main()
{
	bool b1 = integral<int>;
	bool b2 = integral<double>;

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
}
