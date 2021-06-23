#include <iostream>
#include <type_traits>

// ���� C++�� "Ư�� Ÿ��" �� ���� �Լ� �����ε��� ���� �մϴ�.
void foo(int)    {}
void foo(double) {}

// "Ÿ��"�� �ƴ� "Ư�� ������ �����ϴ� Ÿ�Ե�"�� ���� �����ε��� ������
// ���� ������� ?
// void goo(�����Լ����ִ�Ŭ������) {}
// void goo(�����Լ�������Ŭ������) {}

template<typename T>
std::enable_if_t< std::is_polymorphic_v<T>, void >
goo(T a)
{
    std::cout << "Virtual fuction existing Type Algorithm" << std::endl;
}

template<typename T>
std::enable_if_t< !std::is_polymorphic_v<T>, void >
goo(T a)
{
    std::cout << "Virtual fuction not existing Type Algorithm" << std::endl;
}

class Test
{
private:
    /* data */
public:
    Test(/* args */) {}
    ~Test() {}
    virtual void hoo(){}
};


int main()
{
    Test t;
    goo(t);
    return 0;
}