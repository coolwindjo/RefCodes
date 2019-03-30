#include <iostream>

using namespace std;

// Function binding:
// p->cry()를 어떤 function으로 bind할 것인가?
// 1. static binding : Compile 시간에 Compiler가 결정
//                      p의 pointer type으로 결정
//      C, C++, C# (Hot, Trendy)
//              빠르다.
// 2. dynamic binding : Compile 시간에는 p의 memory만 조사하는 기계어 코드 생성
//                      Runtime 에는 memory 조사 후 호출
//      Java, Object-C, keyword "virtual"
//              상대적으로 느리다.
//              reasonable behaviour

class Animal
{
public:
    //virtual void cry()    // Uncomment it for reasonable behaviour!
    void cry()
    {
        cout << "Animal is crying" << endl;
    }
};

class Dog : public Animal
{
public:
    void cry()
    {
        cout << "Dog is barking" << endl;
    }
};

int main()
{
    Animal a; 
    a.cry();
    Dog d;  
    d.cry();

    Animal* p = &d;
    p->cry();

    system("pause");
    return 0;
}


