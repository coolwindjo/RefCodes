#include <iostream>
#include <vector>

using namespace std;

// 핵심: A와 B를 묶고 싶다면 => 공통의 부모를 만들어라!
// up casting은 Public 상속만 가능하다.

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
    //Animal* p = &cat;   // up casting은 Public 상속만 가능하다.

    vector<Animal> animals; // 모든 동물(Animal의 자식들)을 저장 가능하다.
    vector<Dog> dogs;
    vector<Cat> cats;
}


