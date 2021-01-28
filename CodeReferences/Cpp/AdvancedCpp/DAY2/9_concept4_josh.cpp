#include <iostream>
#include <type_traits>

// std::is_integral_v<T>    : type_traits, Type 속성 조사, Template 부분 특수화 문법 사용
// integral                 : concept 문법, Type이 가져야 하는 조건 명시
//                              보다 많은 조건을 만족하는 함수가 선택됨
template<typename T>
concept integral = std::is_integral_v<T>;

// template<typename T> requires std::is_integral_v<T>
template<typename T> requires integral<T> //&& 조건2<T>
void foo(T a) {}

int main()
{
    bool b1 = integral<int>;
    bool b2 = integral<double>;

    std::cout << b1 << std::endl;   // 1
    std::cout << b2 << std::endl;   // 0

    return 0;
}