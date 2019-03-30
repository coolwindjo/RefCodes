#include <iostream>

using namespace std;

// Virtual function table??

class Animal
{
    int age;
public:
    virtual void cry()
    {
        cout << "Animal is crying" << endl;
    }
    virtual void foo() {}
    virtual void goo() {}

};

class Dog : public Animal
{
    int color;
public:
    virtual void cry()  // virtual을 굳이 안써도 부모가 virtual 함수로 선언했으면 속성도 상속됨
    {
        cout << "Dog is barking" << endl;
    }
    virtual void foo() {}
};

int main()
{
    Animal a;
    a.cry();
    Dog d;
    d.cry();

    cout << sizeof(a) << endl;
    cout << sizeof(d) << endl;

    Animal* p = &d;
    p->cry();   // 이순간의 정확한 원리를 생각해봅시다.
    //(*p)[0](p);

    system("pause");
    return 0;
}


