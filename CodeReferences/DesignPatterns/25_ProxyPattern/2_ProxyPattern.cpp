// Remote Proxy - IPC
#include <iostream>
#include "..\ioacademy.h"

using namespace std;
using namespace ioacademy;

// Proxy Pattern
// Remote Proxy: IPC, Network 서버 역할을 대신하는 Class
// Smart Proxy: 기존 요소에 추가적인 작업을 하는 Class

// 서버대신 사용할 Class
class Calc
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
// Server 제작자가 위 Proxy class 제작해서 Client 개발자에게 배포

// 이제 Server 개발자에게 2개의 file을 받아야 한다.
// 1. ICalc.h: Interface header
//  2. CalcProxy.dll: Proxy Class가 있는 .dll

int main()
{
    Calc* pCalc = new Calc;
    cout << pCalc->add(1, 2) << endl;
    cout << pCalc->sub(1, 2) << endl;

    //// 1. Get Server ID
    //int sv_handle = IoFindServer("CalcServer");
    //cout << "Sever ID: " << sv_handle << endl;

    //cout << IoSendServer(sv_handle, 1, 1, 2) << endl;
    //cout << IoSendServer(sv_handle, 2, 1, 2) << endl;

    system("pause");
    return 0;
}