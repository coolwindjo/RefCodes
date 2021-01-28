#include <iostream>

int x = 10;
int& foo(int a, int b)
{
    return x;
}

int main()
{
    auto ret = foo(10, 20);
                // int& 이지만, auto는 참조를 제거하고 Type 결정
                // int ret = foo(10, 20);

    // decltype(함수 호출식)    : 함수 호출의 결과로 나오는 Type 조사
    //                          실체 함수가 호출되는 것은 아님
    decltype( foo(10,20) ) ret2 = foo(10, 20);
                // int& ret = foo(10, 20); 의 의미
    
    // C++14 에서 나온 새로운 기술
    // 우변의 표현식을 auto 자리에 넣어 달라.
    // 결국 "우변으로 Type추론" 단, auto 추론이 아닌 decltype 추론 기술 사용
    decltype(auto) ret3 = foo(10, 20);
                // int& ret3 = foo(10, 20);

    auto&& ret4 = foo(10, 20);  // 우변이 참조 Return 이면 (lvalue)이므로 
                                // int& ret4 = foo(10, 20)
                                // 값 Return이면... rvalue 이므로
                                // int ret4 = foo(10, 20);

    return 0;
}