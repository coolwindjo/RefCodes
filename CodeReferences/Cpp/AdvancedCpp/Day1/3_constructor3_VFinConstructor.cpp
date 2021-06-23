#include <iostream>

// �����ڿ� �����Լ�
// �ٽ� 1. Constructor �ȿ��� Virtual Function�� �������� �ʴ´�.
//			=> �׻� �ڽ��� Member Method�� ȣ���ϰ� �ȴ�.
// 			�ֱ׷���? ��� �������� ���忡�� �����غ���...
//					
struct Base
{
	// /*/
	Base() { goo(); }	// Base::goo
						// Derived::goo �� ȣ���ߴٸ�,
						// �ʱ�ȭ ���� ���� Member attribute (x)�� ����ϰ� �ȴ�.
	void foo() { }
	/*/
	Base() {}
	void foo() { goo(); }
	//*/
	virtual void goo() { std::cout << "Base::goo" << std::endl; }
};

struct Derived : public Base
{
	int x = 10;	// C++: x=10���� Base() �� ���� ȣ��
				// C#: Base()�� ���� ȣ��	����, �̷��� ������ ��õ��
	Derived() : x(10) {}	// Derived(): Base(), x(10) {}

	virtual void goo() override { std::cout << "Derived::goo" << x << std::endl; }
};

int main()
{
	Derived d;
	d.foo();	// Derived::goo
}