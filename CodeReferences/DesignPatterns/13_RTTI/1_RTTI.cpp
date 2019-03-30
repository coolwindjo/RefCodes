#include <iostream>
using namespace std;

// RTTI ( Run-time Type Information )
// 1. ����: ����ð��� p�� ������ � ��ü�� ����Ű���� �����ϴ� ��
// java, C#: Reflection / object-C: Instropection

// 2. Virtual Function Table�� �����Ǵ� type_info�� ����ϹǷ�,
// VFT�� �����ؾ�, ����� �����Ѵ�.

class Animal    // C++���� �� class ũ��� 1�� ������, 
                // �� Class�� VFT�� �������� ����
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
    // � �̸��� ����� ���� ���� �κ��� ǥ�ؿ� ���ǵǾ� ���� �ʽ��ϴ�.

    // ������ type�� ������ ���� �Ʒ��� ���� ���
    if (typeid(*p) == typeid(Dog))
    {
        //,,,
    }
    // ���� p�� Dog��� color�� �����ϰ� �ʹ�.
    // ��, Class�� Virtual Function�� �������� �ʴ´ٸ�, Compile-time��
    // p�� type���� type_info ����ü�� ����� ���� �ڵ带 �����Ѵ�.
    const type_info& t1 = typeid(*p);       // typeid(��ü)
    const type_info& t2 = typeid(Dog);      // typeid(Ŭ����)

    // �����ϰ� �ʹٸ�,
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