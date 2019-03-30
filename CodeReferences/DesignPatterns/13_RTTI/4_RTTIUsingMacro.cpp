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


#define AAA XXX

// Macro ����
// 1. ##: ��ū �ձ�
// 2. # : ��ū ���ڿ�ȭ

// �������� ��ũ�� �Լ��� �����ؾ� �Ѵ�.
// => ��ũ�� ġȯ�� ���� ����ϱ� �����̴�.
// => Linux Kernel
// => MODULE_LINCENSE ��ũ�θ� �м��ϸ� �˴ϴ�.

// �������� ��� Class�� �Ʒ���Ģ�� �����ؾ� �Ѵ�!
// 1. ��� Class�� static member variable �� CRuntimeClass�� �־�� �Ѵ�.
// 2. variable name�� "classŬ�����̸�"���� �Ѵ�.
// 3. static variable�� return�ϴ� virtual function GetRuntimeClass()�� �־�� �Ѵ�.

//---------------------------------------------------------
// �� ��Ģ�� Macro�� ���� �մϴ�.
#define DECLARE_DYNAMIC(class_name)                                 \
    public:                                                         \
    static CRuntimeClass class##class_name;                         \
    virtual CRuntimeClass* GetRunTimeClass();        
    //static CRuntimeClass classAnimal;
    //virtual CRuntimeClass* GetRunTimeClass()


#define IMPLEMENT_DYNAMIC(class_name)                               \
    CRuntimeClass class_name::class##class_name = { #class_name };  \
    CRuntimeClass* class_name::GetRunTimeClass()                                \
    {   return &class##class_name;  }
    //CRuntimeClass Animal::classAnimal = { "Animal" };
    //virtual Animal::CRuntimeClass* GetRunTimeClass()
    //{    return &classAnimal;     }

#define RUNTIME_CLASS(class_name)   &(class_name::class##class_name)


class Animal
{
public:
    DECLARE_DYNAMIC(Animal)
    Animal();
    ~Animal();

private:

};

IMPLEMENT_DYNAMIC(Animal)

Animal::Animal()
{
}

Animal::~Animal()
{
}


class Dog : public Animal
{
public:
    DECLARE_DYNAMIC(Dog)
    Dog();
    ~Dog();

private:

};

IMPLEMENT_DYNAMIC(Dog)

Dog::Dog()
{
}

Dog::~Dog()
{
}



void foo(Animal* p)
{
    if (p->GetRunTimeClass() == RUNTIME_CLASS(Animal))
        cout << "p is a Animal. " << endl;
    else if (p->GetRunTimeClass() == RUNTIME_CLASS(Dog))
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