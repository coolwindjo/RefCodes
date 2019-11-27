#include <iostream>
using namespace std;

/*
1. Parent class�� Destructor�� Virtual Function�̸�, ��� Children�� Destructor�鵵 Virtual Function �̴�.
2. ��� Parent class�� �Ҹ��ڴ� �ݵ�� Virtual Function�̾�� �Ѵ�. 
   (����ϰ��� �ϴ� Class�� Virtual Destructor�� �������� ������ ����ϸ� �ȵȴ�.)
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