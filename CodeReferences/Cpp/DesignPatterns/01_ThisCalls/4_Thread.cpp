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
        CreateThread(0, 0, _thread_loop, this, 0, 0);   // Facade ����
    }

    // 1. �Ʒ��Լ��� Static ��� �Լ� �� �� �ۿ� ���� ������ ��Ȯ�� �˾ƾ� �Ѵ�.
    // 2. this�� �����Ƿ� Thread function parameter�� this�� �����ϴ� ���
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
    t.run();    // �� ���� Thread�� �����Ǿ �����Լ� �� thread_loop()�� ����

    system("pause");
    return 0;
}
