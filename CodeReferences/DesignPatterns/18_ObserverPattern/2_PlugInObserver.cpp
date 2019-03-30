// Observer - Excel �� ǥ�� �̿��� �׷��� �׸��� ��
#include <iostream>
#include <vector>
using namespace std;


const int kMaxNum = 10000;

#if 0
// Observer.h �� �̵��ؾ� �մϴ�.
struct IObserver
{
    virtual void on_update(void* data) = 0;
    virtual ~IObserver() {}
};
#endif

#include "Observer.h"
#include "..\ioacademy.h"
using namespace ioacademy;

class Subject
{
public:
    ~Subject();

    //------------------
    Subject()
    {
        // 1. ��ӵ� ������ ��� DLL�� �����Ѵ�.
        //IoEnumFiles("..\\PlugIn", "*.dll", LoadModule, 0);
        IoEnumFiles("..\\PlugIn", "*.dll", LoadModule, this);
    }

    static int LoadModule(string name, void* param)
    {
        cout << name << endl;

        // 2. DLL�� �ε��Ѵ�.
        void* addr = IoLoadModule(name);        // dlopen

        // 3. ��ӵ� �Լ��� ã�´�.
        typedef IObserver* (*FP)();
        FP f = static_cast<FP>(IoGetFunctionAddress(addr, "CreateGraph"));

        // 4. Graph generation
        IObserver* p = f();

        // 5. Register as an observer.
        Subject* self = static_cast<Subject*>(param);
        self->attach(p);
        
        return 1; // ��� �����ش޶�.
    }

    //------------------

    void attach(IObserver* p)
    {
        v.push_back(p);
    }
    void detach(IObserver* p) {}
    void notify(void* p)
    {
        vector<IObserver*>::iterator a = v.begin();
        //auto at = v.begin();

        for (IObserver* e : v)
        {
            e->on_update(p);
        }
    }

private:
    vector<IObserver*> v;

};

Subject::~Subject()
{
}


// ������ ���: ǥ - (a.k.a. Model)
class Table : public Subject
{
public:
    Table()
    {
        memset(data, 0, sizeof(data));
    }
    ~Table();

    void edit()
    {
        for (int i = 0;
        true
            && (i < kMaxNum); ++i)
        {
            int index;
            cout << "index: "; cin >> index;
            cout << "data: "; cin >> data[index];

            // notify to all observers.
            notify(data);
        }
    }
private:
    int data[5];

};

Table::~Table()
{
}

class PieGraph : public IObserver
{
public:
    virtual void on_update(void* p)
    {
        int* data = static_cast<int*>(p);
        cout << "************* Pie Graph ***********" << endl;
        for (int i = 0; i < 5; ++i)
        {
            cout << i << ":" << data[i] << endl;
        }
    }
private:

};

class BarGraph : public IObserver
{
public:
    virtual void on_update(void* p)
    {
        int* data = static_cast<int*>(p);
        cout << "************* Bar Graph ***********" << endl;
        for (int i = 0; i < 5; ++i)
        {
            cout << i << ":" << data[i] << endl;
        }
    }
private:

};


int main()
{
    Table table;

    PieGraph pg;
    BarGraph bg;

    table.attach(&pg);
    table.attach(&bg);

    table.edit();
}