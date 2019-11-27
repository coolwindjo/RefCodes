//2_SampleGraph
#include <iostream>
using namespace std;

#include "Observer.h"

class SampleGraph : public IObserver
{
public:
    SampleGraph();
    ~SampleGraph();

    virtual void on_update(void* p)
    {
        int* data = static_cast<int*>(p);
        cout << "************* Sample Graph ***********" << endl;
        for (int i = 0; i < 5; ++i)
        {
            cout << i << ":" << data[i] << endl;
        }
    }

private:

};

SampleGraph::SampleGraph()
{
}

SampleGraph::~SampleGraph()
{
}


// 반드시 동적 모듈 안에서 객체를 생성하는 방법을 제공해주어야 한다! - 핵심!!
// - SampleGraph라는 이름은 현재 DLL을 만드는 사람만 알고 있음
// - 프로그램 내부에서는 절대 이름을 사용하면 안됨

// 반드시 DLL 내부에서 자신이 만든 클래스의 Object를 생성해주어야 한다.
// - Function 하나를 약속한다.

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(dllexport)   // Windows에서 DLL 내부 Symbol을 공개하는 방법
    IObserver* CreateGraph()
    {
        return new SampleGraph();
    }


#ifdef __cplusplus
}
#endif

// VS2015용 개발자 명령 프롬프트>> cl 2_SampleGraph.cpp /LD
//  /LD : DLL 로 만들라는 option
// plugin 폴더를 만들어서 2_SampleGraph.dll을 복사해 넣어 준다.
#if 0
void foo() {}->foo

void foo(int) {}->foo@int
void foo(double) {}->foo@double
void foo(int, int) {}->foo@int@int
#endif