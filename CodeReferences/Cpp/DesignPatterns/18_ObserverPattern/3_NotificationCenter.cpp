// 통보센터 (Notification Center)
#include <functional>   // function
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// C++에서 callback을 등록하는 방법은 2가지 형태
// 1. Interface 기반의 객체 등록
//      - 전통적인 Design Pattern (OOP), Observer
// 2. 함수포인터 (function<>)으로 함수 등록
//      - 통보 센터

// iPhone(Mac)에 있는 통보센터를 만들어 봅시다.
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

    // Global center의 개념을 도입하자.
    // Singleton: 오직 한개의 객체를 생성하고 어디서든 동일한 방법으로 접근할 수 있도록
    //            한다.
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


// 중재자(Mediator) 패턴
// - 복잡한 객체간의 관계를 단순화 시켜주는 class

int main()
{
    NotificationCenter nc;
    nc.add_observer("LOWBATTERY", &foo);
    nc.add_observer("LOWBATTERY", bind(&goo, 5));

    Dialog dialog;
    nc.add_observer("LOWBATTERY", bind(&Dialog::warning, &dialog));

    // 이제 배터리를 체크하는 모듈에서 
    nc.postNotificationWithName("LOWBATTERY");

}