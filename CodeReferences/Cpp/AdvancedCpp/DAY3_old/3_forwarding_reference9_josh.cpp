#include <iostream>

template<typename T> class Test
{
private:
    
public:
    Test(){}
    ~Test(){}
    // 아래 Code는 절대 Forwarding reference가 아닙니다.
    // 아래 함수는 Template이 아니고, Class template의 일반 Member 함수 입니다.
    void foo(T&& arg){}

    // forwarding reference가 되려면 "함수 자체가 Template" 이어야 합니다.
    template<typename U> void goo(U&& arg){}
};

int main()
{
    int n = 0;
    Test<int> t;    // 이 때 T는 이미 int로 결정됩니다.
                    // void foo(int&&) 로 결정됨

    // 다음 중 Error를 모드 고르세요.
    // t.foo(n);   // Error
    t.foo(10);  // OK
    t.goo(n);   // OK
    t.goo(10);  // OK
    return 0;
}