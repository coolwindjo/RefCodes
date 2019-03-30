#include "..\ioacademy.h"
using namespace ioacademy;

// 책임의 전가 패턴
// - 이벤트 발생시 처리되지 않을 경우 다음 객체에게 전달한다.
// - 처리할 수 있을 때까지 고리에 따라 이벤트를 전달한다.

// 사용 
// 1) 맥킨토시 계열 - 코코아, 코코아 터치: 리스폰더 체인
//  : View -> ViewController -> AppDelegate

// 2) MFC에서 메뉴 메세지 - 책임의 고리
//  : View -> Document -> Frame -> App

#include <map>
#include <iostream>
using namespace std;
#include <vector>

class Window
{
    static map<int, Window*> this_map;

    int handle;                // C 함수를 통해 윈도우를 실제로 조작하기 위해서는
                               // 반드시 저장해야 한다.

    Window* pParent;             // 부모 윈도우는 1개
    vector<Window*> children;   // 자식은 여러개

public:
    Window()
        : pParent(0)    // 반드시 해줘야 함 =>  하기 싫으면 SmartPointer사용필요
    {}
    void add_child(Window* pW)
    {
        pW->pParent = this;
        children.push_back(pW);

        // C함수로 자식 윈도우를 붙인다.
        IoAddChild(this->handle, pW->handle);
    }

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

class MyWindoow : public Window
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
    w.create();       // 이 순간 윈도우가 만들어져야 합니다.
                      // 왼쪽 버튼을 누르면 "LBUTTON" 이라고 출력되어야 합니다.

    IoProcessMessage();

    system("pause");
    return 0;
}
