#include <iostream>
using namespace std;

// (aka Mixing Template)
// CRTP ( Curiosly Recurring Template Pattern ) - C++ idioms in WTL, Android
// : �����Լ��� ������ �ʰ� �����Լ� ó�� �����ϵ��� ��
// : �θ� Class�� Template�ε� �ڽĿ��� Template�� ���ڷ� �ڽ��� Ÿ���� �����ϴ� ���

// �������� Ȱ���� �����ѵ�, �Ʒ� �ڵ�� �� �����Լ��� �����Լ�ó��
// �����ϰ� ����� ���
// Compile Time�� Static Binding�ǹǷ� Virtual Function���� ������ ����.
// �����ϱ� ������� WTL�� ����

// MS Library �� WTL, ATL(Active X)�� �Ʒ��� ���� ���谡 �Ǿ� �ֽ��ϴ�.
template <typename T>
class Window
{
public:
    Window();
    ~Window();
    void msg_loop()
    {
        //on_click();
        // this: Window*
        (static_cast<T*>(this))->on_click();
    }

    void on_click() {}
private:

};

template <typename T>
Window<T>::Window()
{
}

template <typename T>
Window<T>::~Window()
{
}

class MyWindow : public Window<MyWindow>
{
public:
    MyWindow();
    ~MyWindow();
    void on_click()
    {
        cout << "My Window on click" << endl;
    }
private:

};

MyWindow::MyWindow()
{
}

MyWindow::~MyWindow()
{
}

int main()
{
    MyWindow w;
    w.on_click();

    system("pause");
    return 0;
}