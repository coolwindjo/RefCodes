// State Pattern
// ���¿� ���� ������ ����
//  - Game���� �� �θ� ����Ѵ�.

#include <iostream>
using namespace std;

class Hero
{
public:
    Hero(){}
    ~Hero(){}

    void run() { cout << "run" << endl; }
    void attack() { cout << "attack" << endl; }
private:
    int state;
};

int main()
{
    Hero hero;
    hero.run();
    hero.attack();

    system("pause");
    return 0;
}