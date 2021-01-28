#include <iostream>

int main()
{
    int n = 0;
    int* p = &n;

    // 규칙 1. ()안에 Symbol만 있을 때: 해당 Symbol의 선언을 보고 Type 결정
    decltype(n) d1;     // int d1
    decltype(p) d2;     // int* d2

    // 규칙 2. ()안에 Symbol + 연산자 등의 Expression이 있을 때,
    //          해당 표현식이 lvalue가 될 수 있으면 참조, otherwise 값
    // decltype(*p) d3;    // int& d3; 초기값이 없어서 Error
    // decltype((n)) d4;   // int& d4; 초기값이 없어서 Error
    decltype(n+n) d5;   // int d5;
    // decltype(++n) d6;   // int& d6; 초기값이 없어서 Error

    int x[3] = {1,2,3};
    // decltype(x[0]) d7;  // x[0] = 1 이 된다 => int& d7; 초기값이 없어서 Error

    // x[0] 의 Type은 분명 "int&" 입니다.
    // 그런데, auto가 우변과 완벽히 동일한 Type으로 결정되면 오히려 불편함
    // 그래서, 우변의 "참조, const, volatile" 속성을 버리고 Type 결정
    auto a1 = x[0];

    const int c = 10;
    auto a2 = c;    // a2의 Type은?
    a2 = 20;        // OK

    return 0;
}