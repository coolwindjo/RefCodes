// C++�� ���� Framework���� ��ü������ RTTI�� ������
// ���� �����ؼ� ����ϰ� �ִ�.
// MFC, Qt, Android...

// Object�� Class�� ������ ������ �����ؾ� �Ѵٸ�, => static variable

#include <iostream>
using namespace std;

#include <string>

// RTTI�� �ٽ��� type_info�̴� => static member variable �� ������!
struct CRuntimeClass
{
    string name;
    string author;
    string version;
};

// �������� ��� Class�� �Ʒ���Ģ�� �����ؾ� �Ѵ�!
// 1. ��� Class�� static member variable �� CRuntimeClass�� �־�� �Ѵ�.
// 2. variable name�� "classŬ�����̸�"���� �Ѵ�.
// 3. static variable�� return�ϴ� virtual function GetRuntimeClass()�� �־�� �Ѵ�.

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