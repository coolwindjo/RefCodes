
// 
// Remote Proxy - IPC
#include <iostream>
#include "..\ioacademy.h"

using namespace std;
using namespace ioacademy;

// Proxy Pattern
// Remote Proxy: IPC, Network 서버 역할을 대신하는 Class
// Smart Proxy: 기존 요소에 추가적인 작업을 하는 Class

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