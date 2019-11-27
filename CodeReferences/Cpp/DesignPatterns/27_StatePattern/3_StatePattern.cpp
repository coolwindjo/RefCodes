// State Pattern
// ���¿� ���� ������ ����
//  - Game���� �� �θ� ����Ѵ�.

#include <iostream>
using namespace std;

// ��� 2. ���ϴ� ���� �����Լ��� �и�
//          - item�� ���� ���ϴ� ���� -> �����Լ�

class Hero
{
public:
    Hero() {}
    ~Hero() {}

    virtual void run() { cout << "run" << endl; }
    virtual void attack() { cout << "attack" << endl; }
    int gold;

private:
    int state;
};

// Item�� ȹ�濡 ���� ������ �����ϱ� ���� ����� �����ϸ� �ȴ�.
// �ڽ� Class
class FastItemHero : public Hero
{
public:
    FastItemHero() {}
    ~FastItemHero() {}

    virtual void run() { cout << "Fast run" << endl; }
    virtual void attack() { cout << "Fast attack" << endl; }
private:

};


int main()
{
    Hero normal; FastItemHero fast;
    Hero* pHero = &normal;  // �ʱ� ����
    pHero->attack();
    pHero->run();

    pHero->gold += 100;

    //..... ������ ȹ��
    // ���� �� �ƴ϶� ���µ� ����ȴ�. gold�� ���� �Ǿ�� �Ѵ�.
    pHero = &fast;

    pHero->attack();
    pHero->run();

    system("pause");
    return 0;
}