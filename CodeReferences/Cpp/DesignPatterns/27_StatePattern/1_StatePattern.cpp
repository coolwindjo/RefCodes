// State Pattern
// 상태에 따른 동작의 변경
//  - Game만들 때 널리 사용한다.

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