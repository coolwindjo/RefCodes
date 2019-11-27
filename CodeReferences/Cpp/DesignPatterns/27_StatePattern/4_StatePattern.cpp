// State Pattern
// ���¿� ���� ������ ����
//  - Game���� �� �θ� ����Ѵ�.

#include <iostream>
using namespace std;


// ��� 3. ���ϴ� ���� Interface����� �ٸ� Class�� �и� (Strategy Pattern)
//          - ���¿� ���� ������ ������ interface�� �ʿ�

// ���¿� ���� ������ ������ interface
struct IState
{
    virtual ~IState() {}
    virtual void run() = 0;
    virtual void attack() = 0;
};

// ���뼺�� �������� �и�
// - ������ ���Ͽ��� ���ϴ� ���� �������̽� ����� �ٸ� Ŭ������
//   �и��ϴ� ������ 2���� �Դϴ�.
// 1) Strategy Pattern  - ���ϴ� ���� Policy �� Algorithm
// 2) State Pattern     - ���ϴ� ���� State �� ���� ����
// 3) Builder Pattern

// Refactoring�� �޾� - Replace type code with State or Strategy
// �������� type �߰��� �ʿ��� ���

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
    hero.set_state(&ns);   // �ʱ� ����
    hero.run();
    hero.attack();

    //------------------   ������ ȹ�� (������ ���´� �����ȴ�.)
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

// ��ó�� ����� �������� �ΰ��� �ֽ��ϴ�.
// 1. Reflection �� ���ؼ� 2�� �̻��� ��ü�� ���� �����մϴ�. 
// 2. ��ü�� ����ȭ�� ���ؼ� 2�� �̻��� ��ü�� ���� �� �� �ֽ��ϴ�. 



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

    // int ��� ���� 
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