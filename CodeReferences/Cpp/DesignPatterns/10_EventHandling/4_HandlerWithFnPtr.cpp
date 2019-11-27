// 8_메뉴이벤트4
#include <iostream>
using namespace std;

// 핸들러 방식의 이벤트 처리 
// => 함수 포인터
// => iPhone target-action
//    C#  delegate
//    MFC message map
//    Qt  signal-slot

class Dialog;

class MenuItem
{
    void(Dialog::*handler)();
    Dialog* object;

public:
    void set_handler(void(Dialog::*h)(), Dialog* o)
    {
        handler = h;
        object = o;
    }

    virtual void command()
    {
        (object->*handler)();
    }
};

class Dialog
{
public:
    void open()
    {
        cout << "Dialog opened" << endl;
    }
    void close()
    {
        cout << "Dialog close" << endl;
    }
};


int main()
{
    MenuItem m1;
    MenuItem m2;

    Dialog dlg;
    m1.set_handler(&Dialog::open, &dlg);
    m2.set_handler(&Dialog::close, &dlg);
    m1.command();
    m2.command();

    system("pause");
    return 0;
}
