// 4_���ڷ����� ����
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
        cout << "���� ����ȸ - 2016.12.25" << endl;
    }
};

// ��� ����(������)�� ������ Ư¡�� �θ�� ��������
class Decorator : public Item
{
    Item& item;
};


class Ad1 : public Item
{
    Item& ticket;     // ����� �ռ�
public:
    Ad1(Item& t) : ticket(t) {}

    void print()
    {
        ticket.print();
        cout << "�ڵ��� ����" << endl;
    }
};

class Ad2 : public Item
{
    Item& ticket;
public:
    Ad2(Item& t) : ticket(t) {}

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


