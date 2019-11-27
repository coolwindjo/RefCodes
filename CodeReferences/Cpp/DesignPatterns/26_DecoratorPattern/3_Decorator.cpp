// 4_데코레이터 패턴
#include <iostream>
using namespace std;

class Item
{
public:
    virtual void print() = 0;
    virtual ~Item() {}
};

class Ticket : public Item
{
public:
    void print()
    {
        cout << "작은 음악회 - 2016.12.25" << endl;
    }
};

// 모든 광고(포장지)의 공통의 특징을 부모로 제공하자
class Decorator : public Item
{
    Item& item;
};


class Ad1 : public Item
{
    Item& ticket;     // 재귀적 합성
public:
    Ad1(Item& t) : ticket(t) {}

    void print()
    {
        ticket.print();
        cout << "자동차 광고" << endl;
    }
};

class Ad2 : public Item
{
    Item& ticket;
public:
    Ad2(Item& t) : ticket(t) {}

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


