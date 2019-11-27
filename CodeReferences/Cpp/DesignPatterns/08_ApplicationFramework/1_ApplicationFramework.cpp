#include <iostream>
using namespace std;

// 라이브러리: 프로그램 개발에 필요한 도구를 제공하는 것
//            (class, function)
// 프레임워크: 도구 + 미리 정의된 실행 흐름

// 여기서 부터는 라이브러리 내부코드 입니다. .dll로 숨겨져 있습니다.
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
// 여기서부터는 라이브러리 사용자 코드
// 규칙 1. CWinApp의 파생 클래스를 만들어야 합니다.
// 규칙 2. InitInstance() 가상함수를 재정의해서 초기화 작업을 수행합니다.
// 규칙 3. 사용자가 만든 클래스를 전역적으로 반드시 한개 생성해야 합니다.


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