#include <iostream>
#include <type_traits>

#define CHECK_VALUE_CATEGROY( ... )                     \
    if (std::is_lvalue_reference_v<decltype( (__VA_ARGS__) ) >)   \
        std::cout<< "lvalue" <<std::endl;               \
    else                                                \
        std::cout<< "rvalue" <<std::endl;

int main()
{
    int n = 0;
    ++n;    // lvalue

    // if (std::is_lvalue_reference_v<decltype((EXPRESSION)) >)
    if (std::is_lvalue_reference_v<decltype( (n) ) >)
        std::cout<< "lvalue" <<std::endl;
    else
        std::cout<< "rvalue" <<std::endl;

    std::cout<< "Using MACRO from here ---" <<std::endl;
    CHECK_VALUE_CATEGROY(n);
    CHECK_VALUE_CATEGROY(10);
    CHECK_VALUE_CATEGROY(++n);
    CHECK_VALUE_CATEGROY(n++);

    CHECK_VALUE_CATEGROY("Hello");  // lvalue!!
    //  문자열 literal은 lvalue 입니다.

    return 0;
}