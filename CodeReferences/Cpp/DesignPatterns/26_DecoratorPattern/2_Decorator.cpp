// 4_데코레이터 패턴
#include <iostream>
using namespace std;

class Ticket
{
public:
    void print()
    {
        cout << "작은 음악회 - 2016.12.25" << endl;
    }
};

class Ad1 : public Ticket
{
    Ticket& ticket;
public:
    Ad1(Ticket& t) : ticket(t) {}

    void print()
    {
        ticket.print();
        cout << "자동차 광고" << endl;
    }
};


class Ad2
{
    Ticket& ticket;
public:
    Ad2(Ticket& t) : ticket(t) {}

    void print()
    {
        cout << "TV 광고" << endl;
        ticket.print();
    }

};



int main()
{
    Ticket t;
    // 기능을 추가한 객체에 다시 기능을 추가하고 싶다.
    Ad1 ad1(t);
    Ad2 ad2(ad1);

    ad2.print();

    system("pause");
    return 0;
}

