#include <iostream>
#include <type_traits>

// ���� C++�� "Ư�� Ÿ��" �� ���� �Լ� �����ε��� ���� �մϴ�.
void foo(int)    {}
void foo(double) {}

//foo(1);
//foo(3.4);

// "Ÿ��"�� �ƴ� "Ư�� ������ �����ϴ� Ÿ�Ե�"�� ���� �����ε��� ������
// ���� ������� ?
//void goo(�����Լ����ִ�Ŭ������) {}
//void goo(�����Լ�������Ŭ������) {}

// std::is_polymorphic_v<T> : �����Լ��� ������ true, ������ false 

template<typename T> 
std::enable_if_t< std::is_polymorphic_v<T>, void> 
goo(T a)
{
	std::cout << "�����Լ��� �ִ� Ÿ�Կ� ���� �˰���" << std::endl;
}

template<typename T> 
std::enable_if_t< !std::is_polymorphic_v<T>, void>
goo(T a)
{
	std::cout << "�����Լ��� ���� Ÿ�Կ� ���� �˰���" << std::endl;
}

class Test
{
public:
//	virtual void foo() {}
};

int main()
{
	Test t;
	goo(t);
//	find(x, x + 10, 3);
//	find(x, x + 10, []() {});
}





