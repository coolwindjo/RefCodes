#include "Calc.h"
#include "..\ioacademy.h"
using namespace ioacademy;

class Calc : public ICalc
{
public:
    Calc()
    {
        handle = IoFindServer("CalcServer");
    }

    ~Calc()
    {
    }

    int add(int a, int b) { return IoSendServer(handle, 1, a, b); }
    int sub(int a, int b) { return IoSendServer(handle, 2, a, b); }

private:
    int handle;
};

// DLL ���ʿ��� Proxy�� ����� �Լ��� ���� �����ؾ� �մϴ�.
extern "C" __declspec(dllexport) ICalc* CreateCalc()
{
    return new Calc;
}

// ������ ��� ������Ʈ
// cl CalcProxy.cpp /LD /link user32.lib gdi32.lib kernel32.lib

// cd [���]
// d: