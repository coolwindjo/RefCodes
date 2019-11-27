#include <iostream>
using namespace std;

/*
1. Parent class의 Destructor가 Virtual Function이면, 모든 Children의 Destructor들도 Virtual Function 이다.
2. 모든 Parent class의 소멸자는 반드시 Virtual Function이어야 한다. 
   (상속하고자 하는 Class가 Virtual Destructor를 제공하지 않으면 상속하면 안된다.)
*/
class Base
{
public:
    //~Base()
    virtual ~Base()
    {
        cout << "Resource has not been Freed yet" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Resource Allocation" << endl;
    }
    ~Derived()
    {
        cout << "Resource Free" << endl;
    }
};

int main()
{
    Base *p = new Derived;

    delete p;
    if (1)
    {
        Derived d;
    }
    system("pause");
    return 0;
}