#include "..\ioacademy.h"
using namespace ioacademy;

// å���� ���� ����
// - �̺�Ʈ �߻��� ó������ ���� ��� ���� ��ü���� �����Ѵ�.
// - ó���� �� ���� ������ ���� ���� �̺�Ʈ�� �����Ѵ�.

// ��� 
// 1) ��Ų��� �迭 - ���ھ�, ���ھ� ��ġ: �������� ü��
//  : View -> ViewController -> AppDelegate

// 2) MFC���� �޴� �޼��� - å���� ��
//  : View -> Document -> Frame -> App

#include <map>
#include <iostream>
using namespace std;
#include <vector>

class Window
{
    static map<int, Window*> this_map;

    int handle;                // C �Լ��� ���� �����츦 ������ �����ϱ� ���ؼ���
                               // �ݵ�� �����ؾ� �Ѵ�.

    Window* pParent;             // �θ� ������� 1��
    vector<Window*> children;   // �ڽ��� ������

public:
    Window()
        : pParent(0)    // �ݵ�� ����� �� =>  �ϱ� ������ SmartPointer����ʿ�
    {}
    void add_child(Window* pW)
    {
        pW->pParent = this;
        children.push_back(pW);

        // C�Լ��� �ڽ� �����츦 ���δ�.
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
        case WM_LBUTTONDOWN:    // this�� ���� �Ǿ�� �Ѵ�.
            self->onLButtonDown();
            break;
        case WM_KEYDOWN:
            self->onKeyDown();
            break;
        }

        return 0;
    }
};

// static member variable�� �ܺ� ���Ǹ� �ؾ� �Ѵ�.
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
    w.create();       // �� ���� �����찡 ��������� �մϴ�.
                      // ���� ��ư�� ������ "LBUTTON" �̶�� ��µǾ�� �մϴ�.

    IoProcessMessage();

    system("pause");
    return 0;
}
