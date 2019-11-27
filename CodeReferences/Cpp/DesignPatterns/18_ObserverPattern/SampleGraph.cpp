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


// �ݵ�� ���� ��� �ȿ��� ��ü�� �����ϴ� ����� �������־�� �Ѵ�! - �ٽ�!!
// - SampleGraph��� �̸��� ���� DLL�� ����� ����� �˰� ����
// - ���α׷� ���ο����� ���� �̸��� ����ϸ� �ȵ�

// �ݵ�� DLL ���ο��� �ڽ��� ���� Ŭ������ Object�� �������־�� �Ѵ�.
// - Function �ϳ��� ����Ѵ�.

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(dllexport)   // Windows���� DLL ���� Symbol�� �����ϴ� ���
    IObserver* CreateGraph()
    {
        return new SampleGraph();
    }


#ifdef __cplusplus
}
#endif

// VS2015�� ������ ��� ������Ʈ>> cl 2_SampleGraph.cpp /LD
//  /LD : DLL �� ������ option
// plugin ������ ���� 2_SampleGraph.dll�� ������ �־� �ش�.
#if 0
void foo() {}->foo

void foo(int) {}->foo@int
void foo(double) {}->foo@double
void foo(int, int) {}->foo@int@int
#endif