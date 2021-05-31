#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;  // for _1, _2

void foo(int a, int b, int c, int d)
{
    cout << a << ", " << b << ", " << c << ", " << d <<endl;
}

int main()
{
    foo(1,2,3,4);   // 4 항 함수...
    
    // 4항 함수 => 2항으로...
    bind(&foo, 10, _2, _1, 20 )(1, 2);          // 10, 2, 1, 20

    // 4항 함수 => 3항으로...
    bind(&foo, _3, _2, _1, 100 )(30, 20, 10);   // 10, 20, 30, 100

    // 4항 함수 => 0항으로...
    bind(&foo, 1,2,3,4)();

    modulus<int> m;

    cout << m(10, 3) <<endl;    // 10 % 3
    cout << bind(m, 10, 3)() <<endl;   // 10 % 3
    cout << bind(m, _1, 3)(8) <<endl;   // 8 % 3

    int x[3] = { 1,2,3 };

    // 3의 배수가 아닌 것 찾기
    auto p = find_if( x, x+3, bind(m, _1, 3) );
    cout << *p <<endl;  // 1

    return 0;
}