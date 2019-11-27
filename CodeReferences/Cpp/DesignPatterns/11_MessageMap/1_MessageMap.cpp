// 1_�޼�����

#include "..\ioacademy.h"
using namespace ioacademy;

#include <map>
#include <iostream>
using namespace std;

class Window;
struct AFX_MSG
{
    int message;                // �޼��� ��ȣ
    void(Window::*handler)();   // ó���� �Լ��� �ּ�
};

class Window
{
    static map<int, Window*> this_map;
public:

    // ���� ��� �ڽ� Ŭ������ �ڽ��� ó���ϰ��� �ϴ� �̺�Ʈ��
    // �̺�Ʈ �ڵ鷯�� ���� �迭�� �����ؾ� �Ѵ�.
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
    w.create();       // �� ���� �����찡 ��������� �մϴ�.
                      // ���� ��ư�� ������ "LBUTTON" �̶�� ��µǾ�� �մϴ�.
    IoProcessMessage();

    system("pause");
    return 0;
}