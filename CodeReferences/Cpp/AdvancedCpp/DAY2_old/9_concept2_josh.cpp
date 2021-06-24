#include <iostream>
#include <type_traits>

template<typename T> requires (sizeof(T) >= 1 )
void foo(T a)
{
    std::cout << "1" <<std::endl;
}

template<typename T> requires (sizeof(T) >= 1 && sizeof(T) < 8 )
void foo(T a)
{
    std::cout << "2" <<std::endl;
}

int main()
{
    // foo(3.3);    // 1
    foo(3);       // error: ambiguous foo definition
    return 0;
}