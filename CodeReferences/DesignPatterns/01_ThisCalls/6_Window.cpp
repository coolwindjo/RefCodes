#include "..\ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

#if 0
int foo(int handle, int msg, int param1, int param2)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        cout << "left button down" << endl;
        break;
    case WM_KEYDOWN:
        cout << "key down" << endl;
        break;
    }

    return 0;
}

int main()
{
    int h1 = IoMakeWindow(foo);

    IoProcessMessage();

    system("pause");
    return 0;
}
#endif

class Window
{
    static map<int, Window*> this_map;
public:
    void create()
    {
        int handle = IoMakeWindow(foo);
        this_map[handle] = this;
    }
    
    virtual void onLButtonDown() {}
    virtual void onKeyDown() {}

    static int foo(int handle, int msg, int param1, int param2)
    {
        Window* self = this_map[handle];

        switch (msg)
        {
        case WM_LBUTTONDOWN:    // this가 전달 되어야 한다.
            self->onLButtonDown();
            break;
        case WM_KEYDOWN:
            self->onKeyDown();
            break;
        }

        return 0;
    }
};

// static member variable은 외부 정의를 해야 한다.
map<int, Window*> Window::this_map;

class MyWindoow : public Window     // Facade 개념
{
public:
    virtual void onLButtonDown()
    {
        cout << "LButton" << endl;
    }

    virtual void onKeyDown()
    {
        cout << "Key Down" << endl;
    }
};

int main()
{
    MyWindoow w;
    w.create();

    IoProcessMessage();

    system("pause");
    return 0;
}
