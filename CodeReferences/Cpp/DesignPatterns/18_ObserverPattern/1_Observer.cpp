// Observer - Excel 의 표를 이용한 그래프 그릴때 모델
#include <iostream>
#include <vector>
using namespace std;

const int kMaxNum = 10000;

struct IObserver
{
    virtual void on_update(void* data) = 0;
    virtual ~IObserver() {}
};

// 모든 Table(관찰의 대상)의 특징은 항상 동일하다.
// -> 부모로 제공하자.

// 정리: 달라지는 것은 가상함수화 해서 자식이 변경, 
//       공통적인 것은 부모 클래스로 만들어서 제공

class Subject
{
public:
    Subject();
    ~Subject();

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

Subject::Subject()
{
}

Subject::~Subject()
{
}


// 관찰의 대상: 표 - (a.k.a. Model)
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