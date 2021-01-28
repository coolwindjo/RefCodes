#include <iostream>
#include <type_traits>
#include <concepts>  // predefined concept

template<typename T>
void foo(T a) 
{
    // T가 int를 인자로 해서 호출가능한 Type인지 조사
    bool b = std::predicate<T, int>;

    std::cout << b << std::endl;
}

int main()
{
    foo( 10 );                          // false
    foo( [](int a) { return a < 0; } ); // true
    bool b1 = std::integral<int>;
    bool b2 = std::integral<double>;

    std::cout << b1 << std::endl;   // 1
    std::cout << b2 << std::endl;   // 0

    return 0;
}