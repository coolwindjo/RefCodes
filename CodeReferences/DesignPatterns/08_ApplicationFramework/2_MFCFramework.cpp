// 6_Application Framework 

//----------------------------------
// ���⼭���ʹ� ���̺귯�� ����� �ڵ�
// ��Ģ 1. CWinApp�� �Ļ� Ŭ������ ������ �մϴ�.
// ��Ģ 2. InitInstance() �����Լ��� �������ؼ� �ʱ�ȭ �۾��� �����մϴ�.
// ��Ģ 3. ����ڰ� ���� Ŭ������ ���������� �ݵ�� �Ѱ� �����ؾ� �մϴ�.

// �̸� ���ǵ� �帧 - "template method" ������ ����Ǵ� ��찡 ����.
//                => ��ü���� �帧�� ���̺귯�� �ȿ� �ΰ�, �� �ܰ踦 �����Լ�ȭ�ؼ�
//                   �ڽ��� �������� �� �ֵ���

// Qt - C++
// GTK - C (��ü���� C)
/*
#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance()
    {
        AfxMessageBox(L"���α׷� ����");
        return false;
    }

    virtual int ExitInstance()
    {
        AfxMessageBox(L"���α׷� ����");
        return 0;
    }
};

CMyApp theApp;
*/

int main()
{
    return 0;
}