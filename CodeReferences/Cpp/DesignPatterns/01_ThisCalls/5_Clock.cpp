#include <iostream>
#include <string>
#include <map>

using namespace std;

#include "..\ioacademy.h"
using namespace ioacademy;

#if 0
void foo(int id)
{
    cout << "foo: " << id << endl;
}

int main()
{
    int n1 = IoSetTimer(1000, foo);
    int n2 = IoSetTimer(500, foo);

    IoProcessMessage();

    system("pause");
    return 0;
}
#endif

class Clock;    // 전방선언 - 완전한 선언이 없어도 Pointer는 사용가능

class Clock
{
    string name;
    static map<int, Clock*> this_map;

public:
    Clock(string s)
        : name(s)
    {}

    void start(int ms)
    {
        int id = IoSetTimer(ms, timer_handler);
        this_map[id] = this;    // id 값을 이용해 object addr 저장
    }

    static void timer_handler(int id)
    {
        Clock *self = this_map[id];

        cout << self->name << endl;
    }
};

// static member variable은 외부 정의를 해야 한다.
map<int, Clock*> Clock::this_map;

int main()
{
    Clock c1("AAA");
    Clock c2("\tBBB");

    c1.start(1000);
    c2.start(500);

    IoProcessMessage();

    system("pause");
    return 0;
}