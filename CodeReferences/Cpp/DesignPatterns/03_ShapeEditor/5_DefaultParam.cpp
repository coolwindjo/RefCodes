#include <iostream>
using namespace std;

// Default Parameter�� Compile Time�� Decided
// But, Virtual Function�� Runtime�� Decided

// 1. Default Parameter�� Virtual Function �� ȥ���ϸ� �ȵȴ�!!
// 2. Ȥ��, ����ϰ��� �ϴ� Library�� �̹� ȥ��Ǿ��ִٸ�, ������ �� �� DP�� ���� �������� ����!
// 3. Overloading�� virtual function���� ���̴� Overriding�� ȥ���ϸ� �ȵȴ�.
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