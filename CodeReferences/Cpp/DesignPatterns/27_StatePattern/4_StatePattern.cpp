// State Pattern
// 상태에 따른 동작의 변경
//  - Game만들 때 널리 사용한다.

#include <iostream>
using namespace std;


// 방법 3. 변하는 것을 Interface기반의 다른 Class로 분리 (Strategy Pattern)
//          - 상태에 따른 동작을 정의한 interface가 필요

// 상태에 따른 동작을 정의한 interface
struct IState
{
    virtual ~IState() {}
    virtual void run() = 0;
    virtual void attack() = 0;
};

// 공통성과 가변성의 분리
// - 디자인 패턴에서 변하는 것을 인터페이스 기반의 다른 클래스로
//   분리하는 패턴은 2가지 입니다.
// 1) Strategy Pattern  - 변하는 것이 Policy 나 Algorithm
// 2) State Pattern     - 변하는 것이 State 에 따른 동작
// 3) Builder Pattern

// Refactoring의 겪언 - Replace type code with State or Strategy
// 지속적인 type 추가가 필요한 경우

class Hero
{
public:
    Hero()
        : state(nullptr)
    {}
    ~Hero() {}

    void set_state(IState* p) { state = p; }

    void run() { state->run(); }
    void attack() { state->attack(); }

private:
    IState* state;
};



class NormalState : public IState
{
public:
    virtual void run() { cout << "run" << endl; }
    virtual void attack() { cout << "attack" << endl; }
};

class FastState : public IState
{
public:
    virtual void run() { cout << "fast run" << endl; }
    virtual void attack() { cout << "fast attack" << endl; }
};


int main()
{
    NormalState ns; FastState fs;
    Hero hero;
    hero.set_state(&ns);   // 초기 상태
    hero.run();
    hero.attack();

    //------------------   아이템 획득 (이전의 상태는 공유된다.)
    hero.set_state(&fs);
    hero.run();
    hero.attack();

    system("pause");
    return 0;
}


#if 0
// enum Singleton
enum Singleton {
    INSTANCE;
}

class Singleton {
    private static final Singleton INSTANCE = new Singleton();

    private Singleton() {}

    public Singleton getInstance() {
        return INSTANCE;
    }
}

// 위처럼 만들면 문제점이 두가지 있습니다.
// 1. Reflection 을 통해서 2개 이상의 객체를 생성 가능합니다. 
// 2. 객체를 직렬화를 통해서 2개 이상의 객체를 생성 할 수 있습니다. 



// enum class
enum State
{
    FAST{
    @Override
    void run() {
    System.out.println("fast run");
}

},
NORMAL{
    @Override
    void run() {
    System.out.println("run");
}
};

abstract void run();
}


class Hero {

    // int 상수 패턴 
    private static final int STATE_FAST = 0;
    private static final int STATE_NORMAL = 1;

    // int state;


    private State state;

    public void setState(State state) {
        this.state = state;
    }

    void run() {
        state.run();
    }
}

public class Test {
    public static void main(String[] args) {
        Hero hero = new Hero();
        hero.setState(State.NORMAL);
        hero.run();

        hero.setState(State.FAST);
        hero.run();
    }
}


#endif