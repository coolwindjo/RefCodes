#include <iostream>

// int check(int a) {}
// char check(double d) {}

// 핵심 1. 평가되지 않은 표현식에 넣는 함수는 선언만 있으면 가능
//      2. sizeof() 
int check(int a) {}
char check(double d) {}

int main()
{
    int n = sizeof(check(3.4));

    std::cout<< n <<std::endl;  // 1
    return 0;
}