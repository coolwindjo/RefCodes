#include <iostream>
using namespace std;

// Default Parameter는 Compile Time에 Decided
// But, Virtual Function은 Runtime에 Decided

// 1. Default Parameter와 Virtual Function 은 혼용하면 안된다!!
// 2. 혹시, 사용하고자 하는 Library에 이미 혼용되어있다면, 재정의 할 때 DP를 절대 변경하지 말자!
// 3. Overloading과 virtual function에서 쓰이는 Overriding도 혼용하면 안된다.
class A
{
public:
    virtual void foo(int a = 10)
    {
        cout << "A : " << a << endl;
    }
};

class B : public A  // Inherence
{
    int b;
public:
    virtual void foo(int a = 20)
    {
        cout << "B :" << a << endl;
    }
};

int main()
{
    A* p = new B;

    p->foo();

    system("pause");
    return 0;
}