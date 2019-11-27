// 3_프록시3
// 서버 제작자에게서 ICalc.h와 CalcProxy.dll을 받아야 합니다.
#include <iostream>
#include "..\ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "Calc.h"

int main()
{
    // 1. CalcProxy.dll을 로드 합니다.
    void* addr = IoLoadModule("CalcProxy.dll");

    // 2. Calc 객체 생성하는 함수를 찾아야 합니다.
    typedef ICalc*(*F)();
    F f = (F)IoGetFunctionAddress(addr, "CreateCalc");

    // 3. Calc 객체 생성
    ICalc* pCalc = f();

    // 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
    cout << pCalc->add(10, 20) << endl;
    cout << pCalc->sub(10, 20) << endl;

    system("pause");
    return 0;
}
