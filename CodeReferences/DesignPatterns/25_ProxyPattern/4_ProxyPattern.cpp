// 3_프록시3
// 서버 제작자에게서 ICalc.h와 CalcProxy.dll을 받아야 합니다.
#include <iostream>
#include "..\ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "Calc.h"

int main()
{
    ICalc* pCalc = CreateInstance();

    // 이제는 서버의 존재를 모르고도 기능을 수행할 수 있습니다.
    cout << pCalc->add(10, 20) << endl;
    cout << pCalc->sub(10, 20) << endl;

    //delete pCalc;       // 절대하면 안됨  => Reference Counter 기반으로 Object관리 필요

    // dll을 만들 때와 dll을 사용하는 코드의 컴파일러 버전이 달라도
    // 같은 컴파일러에서 new와 delete의 코드가 생성되어야 한다.
    // -> 참조 계수 기반 객체 수명 관리
    system("pause");
    return 0;
}

