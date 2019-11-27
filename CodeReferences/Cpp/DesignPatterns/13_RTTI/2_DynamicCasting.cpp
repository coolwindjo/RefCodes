#include <iostream>
using namespace std;

// RTTI ( Run-time Type Information )
// 1. 개념: 실행시간에 p가 정말로 어떤 객체를 가리키는지 조사하는 것
// java, C#: Reflection / object-C: Instropection

// 2. Virtual Function Table로 관리되는 type_info를 사용하므로,
// VFT이 존재해야, 제대로 동작한다.

class Animal    // C++에서 빈 class 크기는 1로 설정됨, 
                // 빈 Class는 VFT가 존재하지 않음
{
public:
    Animal();
    //~Animal();
    virtual ~Animal();

private:

};

Animal::Animal()
{
}

Animal::~Animal()
{
}


class Dog : public Animal
{
public:
    Dog();
    ~Dog();

//private:
    int color;
};

Dog::Dog()
{
}

Dog::~Dog()
{
}


void foo(Animal* p)
{
    // Down casting
    // 1) static_cast (in Compile-time)
    // 장점: casting이 Compile-time에 수행되므로 성능저하가 없다.
    //      의도한 설계가, 의도한 자식만이 오도록 되어 있다면
    //      반드시 static_cast를 사용해야 한다.
    // 문제점: 잘못된 Down casting을 detect할 수 없다.
    /* <- "/"
    Dog* pDog = static_cast<Dog*>(p);
    pDog->color = 20;
    /*/
    // 2) dynamic_cast (in Run-time)
    // 장점: 내부적으로 RTTI를 이용하여 구현되므로, 잘못된 Down casting을
    //      detect할 수 있다. 즉, 잘못된 casting은 NULL을 return 한다.
    // 단점: 느리다. 꼭 필요할 때만 사용해야 한다.
    Dog* pDog = dynamic_cast<Dog*>(p);
    cout << pDog << endl;
    //*/
}

int main()
{
    Animal a;
    Dog d;

    foo(&a);
    foo(&d);

    system("pause");
    return 0;
}