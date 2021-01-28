#include <iostream>
#include <type_traits>

// Type이 가져야 하는 조건을 명시하는 "Concept 문법"의 도입
template<typename T>
concept MoreThan1 = sizeof(T) > 1;
template<typename T>
concept LessThan8 = sizeof(T) < 8;

template<typename T>
concept Addable = requires(T a, T b)
{
    typename T::value_type;
    T();
    a + b;  // 덧셈이 가능해야 한다는 조건
};

// template<typename T> requires (sizeof(T) >= 1 )
template<typename T> requires MoreThan1<T>
void foo(T a)
{
    std::cout << "1" <<std::endl;
}

// template<typename T> requires (sizeof(T) >= 1 && sizeof(T) < 8 )
template<typename T> requires MoreThan1<T> && LessThan8<T>
void foo(T a)
{
    std::cout << "2" <<std::endl;
}

int main()
{
    // foo(3.3);    // 1
    foo(3);       // Error: ambiguous foo definition
    return 0;
}