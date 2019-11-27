// State Pattern
// 상태에 따른 동작의 변경
//  - Game만들 때 널리 사용한다.

#include <iostream>
using namespace std;

// 방법 2. 변하는 것을 가상함수로 분리
//          - item에 따라 변하는 동작 -> 가상함수

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

// Item에 획득에 따라 동작을 변경하기 위해 상속을 적용하면 된다.
// 자식 Class
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
    Hero* pHero = &normal;  // 초기 상태
    pHero->attack();
    pHero->run();

    pHero->gold += 100;

    //..... 아이템 획득
    // 동작 뿐 아니라 상태도 변경된다. gold는 공유 되어야 한다.
    pHero = &fast;

    pHero->attack();
    pHero->run();

    system("pause");
    return 0;
}