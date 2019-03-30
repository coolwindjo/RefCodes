#include <iostream>

using namespace std;

// Function binding:
// p->cry()�� � function���� bind�� ���ΰ�?
// 1. static binding : Compile �ð��� Compiler�� ����
//                      p�� pointer type���� ����
//      C, C++, C# (Hot, Trendy)
//              ������.
// 2. dynamic binding : Compile �ð����� p�� memory�� �����ϴ� ���� �ڵ� ����
//                      Runtime ���� memory ���� �� ȣ��
//      Java, Object-C, keyword "virtual"
//              ��������� ������.
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


