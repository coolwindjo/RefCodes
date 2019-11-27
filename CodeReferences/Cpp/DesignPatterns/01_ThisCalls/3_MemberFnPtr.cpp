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

    static void goo()   // 정적 Member function
    {
        cout << "goo" << endl;
    }
};

void foo()              // 일반 function
{
    cout << "foo" << endl;
}

int main()
{
    // 1. 일반 함수 포인터에 멤버함수의 주소를 담을 수 없다.
    void(*f1)() = &foo;
    f1();

    //void(*f1)() = &Dialog::close;   
    void(Dialog::*f2)() = &Dialog::close; 
    //f1();   // => Error!

    // 2. 멤버 함수 포인터를 만들고 사용하는 방법
    Dialog dlg;
    //Dialog::f2();     // => Error!
    //dlg.*f2();        // => Error!
    //dlg.(*f2)();      // => Error!
    (dlg.*f2)();

    // 3. 일반 함수 포인터에 정적 멤버 함수의 주소를 담을 수 있다.
    void(*f3)() = &Dialog::goo;
    f3();

}