#include <iostream>
using namespace std;

// ���̺귯��: ���α׷� ���߿� �ʿ��� ������ �����ϴ� ��
//            (class, function)
// �����ӿ�ũ: ���� + �̸� ���ǵ� ���� �帧

// ���⼭ ���ʹ� ���̺귯�� �����ڵ� �Դϴ�. .dll�� ������ �ֽ��ϴ�.
class CWinApp;
CWinApp* g_app;

class CWinApp
{
public:
    CWinApp() 
    {
        g_app = this;
    }
    virtual bool InitInstance()
    {
        return false;
    }
    virtual int ExitInstance()
    {
        return 0;
    }
    virtual int Run()
    {
        return 0;
    }

private:

};

CWinApp* AfxGetApp() 
{
    return g_app;
}

int main()
{
    CWinApp* pApp = AfxGetApp();

    if (pApp->InitInstance())
        pApp->Run();

    pApp->ExitInstance();
}

//----------------------------------
// ���⼭���ʹ� ���̺귯�� ����� �ڵ�
// ��Ģ 1. CWinApp�� �Ļ� Ŭ������ ������ �մϴ�.
// ��Ģ 2. InitInstance() �����Լ��� �������ؼ� �ʱ�ȭ �۾��� �����մϴ�.
// ��Ģ 3. ����ڰ� ���� Ŭ������ ���������� �ݵ�� �Ѱ� �����ؾ� �մϴ�.


class CMyApp : public CWinApp
{
public:
    virtual bool InitInstance()
    {
        cout << "Program starts" << endl;
        return false;
    }

    virtual int ExitInstance()
    {
        cout << "Program finished" << endl;
        return 0;
    }

private:

};

CMyApp theApp;