#include <iostream>
#include <vector>

using namespace std;

// �ٽ�: A�� B�� ���� �ʹٸ� => ������ �θ� ������!
// up casting�� Public ��Ӹ� �����ϴ�.

class Animal
{

};

class Dog : public Animal
{

};

class Cat : private Animal
{

};

int main()
{
    Dog dog;
    Cat cat;
    Animal* p = &dog;
    //Animal* p = &cat;   // up casting�� Public ��Ӹ� �����ϴ�.

    vector<Animal> animals; // ��� ����(Animal�� �ڽĵ�)�� ���� �����ϴ�.
    vector<Dog> dogs;
    vector<Cat> cats;
}


