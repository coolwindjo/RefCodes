
// 
// Remote Proxy - IPC
#include <iostream>
#include "..\ioacademy.h"

using namespace std;
using namespace ioacademy;

// Proxy Pattern
// Remote Proxy: IPC, Network ���� ������ ����ϴ� Class
// Smart Proxy: ���� ��ҿ� �߰����� �۾��� �ϴ� Class

int main()
{
    // 1. Get Server ID
    int handle = IoFindServer("CalcServer");
    cout << "Sever ID: " << handle << endl;

    cout << IoSendServer(handle, 1, 1, 2) << endl;
    cout << IoSendServer(handle, 2, 1, 2) << endl;

    system("pause");
    return 0;
}