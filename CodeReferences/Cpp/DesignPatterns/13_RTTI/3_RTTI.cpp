// C++의 많은 Framework들이 자체적으로 RTTI의 개념을
// 직접 구현해서 사용하고 있다.
// MFC, Qt, Android...

// Object와 Class가 동일한 변수를 공유해야 한다면, => static variable

#include <iostream>
using namespace std;

#include <string>

// RTTI의 핵심은 type_info이다 => static member variable 로 만들자!
struct CRuntimeClass
{
    string name;
    string author;
    string version;
};

// 이제부터 모든 Class는 아래규칙을 만족해야 한다!
// 1. 모든 Class는 static member variable 인 CRuntimeClass가 있어야 한다.
// 2. variable name은 "class클래스이름"으로 한다.
// 3. static variable을 return하는 virtual function GetRuntimeClass()가 있어야 한다.

class Animal
{
public:
    static CRuntimeClass classAnimal;
    virtual CRuntimeClass* GetRunTimeClass()
    {
        return &classAnimal;
    }
    Animal();
    ~Animal();

private:

};

Animal::Animal()
{
}

Animal::~Animal()
{
}

CRuntimeClass Animal::classAnimal = { "Animal" };

class Dog : public Animal
{
public:
    static CRuntimeClass classDog;
    virtual CRuntimeClass* GetRunTimeClass()
    {
        return &classDog;
    }
    Dog();
    ~Dog();
    
private:
    
};

Dog::Dog()
{
}

Dog::~Dog()
{
}

CRuntimeClass Dog::classDog = { "Dog" };

void foo(Animal* p)
{
    if (p->GetRunTimeClass() == &Animal::classAnimal)
        cout << "p is a Animal. " << endl;
    else if (p->GetRunTimeClass() == &Dog::classDog)
        cout << "p is a Dog. " << endl;
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