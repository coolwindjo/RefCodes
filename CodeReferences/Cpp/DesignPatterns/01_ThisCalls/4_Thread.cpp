#include <Windows.h>
#include <iostream>

using namespace std;

#if 0
#include "Thread.h"
DWORD __stdcall foo(void* p)
{
    cout << "Thread start!!" << endl;
    return 0;
}

int main()
{
    CreateThread(0, 0/*stack size*/, foo/*function pointer*/, 0/*parameter transfer*/, 0/*action order*/, 0/*address allocation*/);
    system("pause");
    return 0;
}
#endif

class Thread
{
public:
    void run()
    {
        CreateThread(0, 0, _thread_loop, this, 0, 0);   // Facade 개념
    }

    // 1. 아래함수가 Static 멤버 함수 일 수 밖에 없는 이유를 정확히 알아야 한다.
    // 2. this가 없으므로 Thread function parameter로 this를 전달하는 기술
    static DWORD __stdcall _thread_loop(void* user)
    {
        Thread* self = static_cast<Thread*>(user);

        self->thread_loop();    // thread_loop(self);

        return 0;
    }

    virtual bool thread_loop() { return false; }

};


// Library User Class.
class MyThread : public Thread
{
public:
    virtual bool thread_loop()
    {
        cout << "MyThread thread_loop()" << endl;
        return true;
    }
};

int main()
{
    MyThread t;
    t.run();    // 이 순간 Thread가 생성되어서 가상함수 인 thread_loop()를 수행

    system("pause");
    return 0;
}
