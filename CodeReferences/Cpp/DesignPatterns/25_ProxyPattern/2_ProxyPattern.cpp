// Remote Proxy - IPC
#include <iostream>
#include "..\ioacademy.h"

using namespace std;
using namespace ioacademy;

// Proxy Pattern
// Remote Proxy: IPC, Network ���� ������ ����ϴ� Class
// Smart Proxy: ���� ��ҿ� �߰����� �۾��� �ϴ� Class

// ������� ����� Class
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
// Server �����ڰ� �� Proxy class �����ؼ� Client �����ڿ��� ����

// ���� Server �����ڿ��� 2���� file�� �޾ƾ� �Ѵ�.
// 1. ICalc.h: Interface header
//  2. CalcProxy.dll: Proxy Class�� �ִ� .dll

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