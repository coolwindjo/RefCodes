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


#define AAA XXX

// Macro 문법
// 1. ##: 토큰 잇기
// 2. # : 토큰 문자열화

// 이중으로 매크로 함수를 제공해야 한다.
// => 매크로 치환과 같이 사용하기 위함이다.
// => Linux Kernel
// => MODULE_LINCENSE 매크로를 분석하면 됩니다.

// 이제부터 모든 Class는 아래규칙을 만족해야 한다!
// 1. 모든 Class는 static member variable 인 CRuntimeClass가 있어야 한다.
// 2. variable name은 "class클래스이름"으로 한다.
// 3. static variable을 return하는 virtual function GetRuntimeClass()가 있어야 한다.

//---------------------------------------------------------
// 위 규칙을 Macro로 구현 합니다.
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