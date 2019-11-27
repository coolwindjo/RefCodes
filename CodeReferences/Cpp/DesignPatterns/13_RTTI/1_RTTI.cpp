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
    //* <- "/"
    ~Animal();
    /*/
    virtual ~Animal();
    //*/
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

private:
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
    cout << typeid(*p).name() << endl;
    // 어떤 이름을 출력할 지에 대한 부분이 표준에 정의되어 있지 않습니다.

    // 실제로 type을 조사할 때는 아래와 같이 사용
    if (typeid(*p) == typeid(Dog))
    {
        //,,,
    }
    // 만약 p가 Dog라면 color에 접근하고 싶다.
    // 즉, Class에 Virtual Function이 존재하지 않는다면, Compile-time에
    // p의 type으로 type_info 구조체를 만드는 기계어 코드를 생성한다.
    const type_info& t1 = typeid(*p);       // typeid(객체)
    const type_info& t2 = typeid(Dog);      // typeid(클래스)

    // 조사하고 싶다면,
    if (t1 == t2)
    {
        cout << "p is a Dog, and the class size is " << sizeof(Dog) << endl;
    }
    else
    {
        cout << "p is an Animal, and the class size is " << sizeof(Animal) << endl;
    }
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