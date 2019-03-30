// 1_메세지맵

#include "..\ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

class Window;
struct AFX_MSG
{
    int message;                // 메세지 번호
    void(Window::*handler)();   // 처리할 함수의 주소
};

class Window
{
    static map<int, Window*> this_map;
public:

    // 이제 모든 자식 클래스는 자신이 처리하고자 하는 이벤트와
    // 이벤트 핸들러를 담은 배열을 리턴해야 한다.
    virtual AFX_MSG* GetMessageMap() { return 0; }


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
        case WM_LBUTTONDOWN:
            self->onLButtonDown();
            break;

        case WM_KEYDOWN:
            self->onKeyDown();
            break;
        }

        return 0;
    }


};

map<int, Window*> Window::this_map;

class MyWindow : public Window
{
public:
    virtual void onLButtonDown() {
        cout << "LButton" << endl;
    }

    virtual void onKeyDown() {
        cout << "Key Down" << endl;
    }
};


int main()
{
    MyWindow w;
    w.create();       // 이 순간 윈도우가 만들어져야 합니다.
                      // 왼쪽 버튼을 누르면 "LBUTTON" 이라고 출력되어야 합니다.
    IoProcessMessage();

    system("pause");
    return 0;
}