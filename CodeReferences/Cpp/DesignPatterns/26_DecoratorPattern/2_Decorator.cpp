// 4_���ڷ����� ����
#include <iostream>
using namespace std;

class Ticket
{
public:
    void print()
    {
        cout << "���� ����ȸ - 2016.12.25" << endl;
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
        cout << "�ڵ��� ����" << endl;
    }
};


class Ad2
{
    Ticket& ticket;
public:
    Ad2(Ticket& t) : ticket(t) {}

    void print()
    {
        cout << "TV ����" << endl;
        ticket.print();
    }

};



int main()
{
    Ticket t;
    // ����� �߰��� ��ü�� �ٽ� ����� �߰��ϰ� �ʹ�.
    Ad1 ad1(t);
    Ad2 ad2(ad1);

    ad2.print();

    system("pause");
    return 0;
}

