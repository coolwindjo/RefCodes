#include <iostream>
#include <vector>

// Effective Modern C++
// Effective C++, More Effective C++
int main()
{
    std::vector<int> v1 = {1,1,1};
    std::vector<bool> v2 = {1,1,1};

    // a1과 a2의 Type을 예측해보세요.
    auto a1 = v1[0];    // int a1 = v1[0];
    auto a2 = v2[0];    // BitProxy a2 = v2[0];

    std::cout<< typeid(a1).name() <<std::endl;
    std::cout<< typeid(a2).name() <<std::endl;

    // 아래 Code를 생각해보세요.
    auto& r1 = v1[0];   // OK. operator[] 연산자가 참조 반환
    // auto& r2 = v2[0];   // Error. operator[] 가 임시객체(rvalue) 반환
    auto&& r3 = v2[0];  //OK

    // for (auto& n : v2) {} // Error

    return 0;
}