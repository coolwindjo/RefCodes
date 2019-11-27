// 3_���Ͻ�3
// ���� �����ڿ��Լ� ICalc.h�� CalcProxy.dll�� �޾ƾ� �մϴ�.
#include <iostream>
#include "..\ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "Calc.h"

int main()
{
    // 1. CalcProxy.dll�� �ε� �մϴ�.
    void* addr = IoLoadModule("CalcProxy.dll");

    // 2. Calc ��ü �����ϴ� �Լ��� ã�ƾ� �մϴ�.
    typedef ICalc*(*F)();
    F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

    // 3. Calc ��ü ����
    ICalc* pCalc = f();

    // ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
    cout << pCalc->add(10, 20) << endl;
    cout << pCalc->sub(10, 20) << endl;

    system("pause");
    return 0;
}
