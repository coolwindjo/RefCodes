// �뺸���� (Notification Center)
#include <functional>   // function
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// C++���� callback�� ����ϴ� ����� 2���� ����
// 1. Interface ����� ��ü ���
//      - �������� Design Pattern (OOP), Observer
// 2. �Լ������� (function<>)���� �Լ� ���
//      - �뺸 ����

// iPhone(Mac)�� �ִ� �뺸���͸� ����� ���ô�.
class NotificationCenter
{
public:
    NotificationCenter();
    ~NotificationCenter();

private:
    typedef function<void()> HANDLER;

    map<string, vector<HANDLER>> notifi_map;
public:
    void add_observer(string key, HANDLER handler)
    {
        notifi_map[key].push_back(handler);
    }

    void postNotificationWithName(string key)
    {
        vector<HANDLER>& v = notifi_map[key];
        for (HANDLER e : v)
        {
            e();
        }
    }

    // Global center�� ������ ��������.
    // Singleton: ���� �Ѱ��� ��ü�� �����ϰ� ��𼭵� ������ ������� ������ �� �ֵ���
    //            �Ѵ�.
    static  NotificationCenter& default_center()
    {
        static NotificationCenter instance;
        return instance;
    }

};

NotificationCenter::NotificationCenter()
{
}

NotificationCenter::~NotificationCenter()
{
}

//----------------------------------------------------

void foo() { cout << "foo" << endl; }
void goo(int n) { cout << "goo: " << n << endl; }

class Dialog
{
public:
    Dialog();
    ~Dialog();
    void warning() { cout << "Warning dialog" << endl; }

private:

};

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

//-------------------------------------------------------


// ������(Mediator) ����
// - ������ ��ü���� ���踦 �ܼ�ȭ �����ִ� class

int main()
{
    NotificationCenter nc;
    nc.add_observer("LOWBATTERY", &foo);
    nc.add_observer("LOWBATTERY", bind(&goo, 5));

    Dialog dialog;
    nc.add_observer("LOWBATTERY", bind(&Dialog::warning, &dialog));

    // ���� ���͸��� üũ�ϴ� ��⿡�� 
    nc.postNotificationWithName("LOWBATTERY");

}