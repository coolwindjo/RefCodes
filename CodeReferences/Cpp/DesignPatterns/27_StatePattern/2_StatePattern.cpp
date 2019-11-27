// State Pattern
// 상태에 따른 동작의 변경
//  - Game만들 때 널리 사용한다.

#include <iostream>
using namespace std;

// 방법 1. 아이템의 종류에 따른 조건 분기

class Hero
{
public:
    Hero() {}
    ~Hero() {}

    // 문제점: OCP를 만족할 수 없다.
    //  - 신규 아이템이 추가되면 조건분기문이 추가되어야 한다.
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