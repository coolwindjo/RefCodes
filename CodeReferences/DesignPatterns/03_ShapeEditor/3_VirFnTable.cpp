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
    virtual void cry()  // virtual�� ���� �Ƚᵵ �θ� virtual �Լ��� ���������� �Ӽ��� ��ӵ�
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
    p->cry();   // �̼����� ��Ȯ�� ������ �����غ��ô�.
    //(*p)[0](p);

    system("pause");
    return 0;
}


