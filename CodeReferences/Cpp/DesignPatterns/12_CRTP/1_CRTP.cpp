#include <iostream>
using namespace std;

// (aka Mixing Template)
// CRTP ( Curiosly Recurring Template Pattern ) - C++ idioms in WTL, Android
// : 가상함수로 만들지 않고 가상함수 처럼 동작하도록 함
// : 부모 Class가 Template인데 자식에서 Template의 인자로 자신의 타입을 전달하는 기술

// 여러가지 활용이 가능한데, 아래 코드는 비 가상함수를 가상함수처럼
// 동작하게 만드는 기법
// Compile Time에 Static Binding되므로 Virtual Function보다 성능이 좋다.
// 이해하기 어려워서 WTL은 망함

// MS Library 중 WTL, ATL(Active X)가 아래와 같이 설계가 되어 있습니다.
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