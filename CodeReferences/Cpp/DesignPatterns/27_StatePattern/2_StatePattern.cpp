// State Pattern
// ���¿� ���� ������ ����
//  - Game���� �� �θ� ����Ѵ�.

#include <iostream>
using namespace std;

// ��� 1. �������� ������ ���� ���� �б�

class Hero
{
public:
    Hero() {}
    ~Hero() {}

    // ������: OCP�� ������ �� ����.
    //  - �ű� �������� �߰��Ǹ� ���Ǻб⹮�� �߰��Ǿ�� �Ѵ�.
    void run()
    {
        if (state = 1)
        {
            cout << "run" << endl;
        }
        else if(state = 2)
        {
            cout << "fast run" << endl;
        }
    }
    void attack() { cout << "attack" << endl; }

    void set_state(int s) {
        state = s;
    }

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