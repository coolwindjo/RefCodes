// Member function & function pointer
#include <iostream>

using namespace std;

class Dialog
{
public:
    void close()        // Member function
    {
        cout << "Dialog close" << endl;
    }

    static void goo()   // ���� Member function
    {
        cout << "goo" << endl;
    }
};

void foo()              // �Ϲ� function
{
    cout << "foo" << endl;
}

int main()
{
    // 1. �Ϲ� �Լ� �����Ϳ� ����Լ��� �ּҸ� ���� �� ����.
    void(*f1)() = &foo;
    f1();

    //void(*f1)() = &Dialog::close;   
    void(Dialog::*f2)() = &Dialog::close; 
    //f1();   // => Error!

    // 2. ��� �Լ� �����͸� ����� ����ϴ� ���
    Dialog dlg;
    //Dialog::f2();     // => Error!
    //dlg.*f2();        // => Error!
    //dlg.(*f2)();      // => Error!
    (dlg.*f2)();

    // 3. �Ϲ� �Լ� �����Ϳ� ���� ��� �Լ��� �ּҸ� ���� �� �ִ�.
    void(*f3)() = &Dialog::goo;
    f3();

}