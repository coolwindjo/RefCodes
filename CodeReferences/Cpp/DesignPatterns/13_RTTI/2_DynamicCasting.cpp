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
    // ����: casting�� Compile-time�� ����ǹǷ� �������ϰ� ����.
    //      �ǵ��� ���谡, �ǵ��� �ڽĸ��� ������ �Ǿ� �ִٸ�
    //      �ݵ�� static_cast�� ����ؾ� �Ѵ�.
    // ������: �߸��� Down casting�� detect�� �� ����.
    /* <- "/"
    Dog* pDog = static_cast<Dog*>(p);
    pDog->color = 20;
    /*/
    // 2) dynamic_cast (in Run-time)
    // ����: ���������� RTTI�� �̿��Ͽ� �����ǹǷ�, �߸��� Down casting��
    //      detect�� �� �ִ�. ��, �߸��� casting�� NULL�� return �Ѵ�.
    // ����: ������. �� �ʿ��� ���� ����ؾ� �Ѵ�.
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