#include <iostream>
using namespace std;

class A
{
    int a;
public:
    //void foo()
    virtual void foo()
    {
        cout << "A foo" << endl;
    }
};

class B
{
    int b;
public:
    //void goo()
    virtual void goo()
{
        cout << "B goo" << endl;
    }
};

int main()
{
    A aaa;
    B* p = reinterpret_cast<B*>(&aaa);

    p->goo();

    system("pause");
    return 0;
}