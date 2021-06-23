#include <iostream>

// �����ڿ� �����Լ�
// �ٽ� 1. ������ �ȿ����� �����Լ��� �������� �ʽ��ϴ�.
//			�׻� �ڽ��� ����� ȣ���ϰ� �˴ϴ�.
// �� �̷��� ���� ������� ? ��� �����ڸ� ������ ������..
struct Base
{
	Base() { goo(); } // Base::goo
					// Derived::goo �� ȣ���ߴٸ� �ʱ�ȭ ���� ���� ��� ����Ÿ(x)��
					// ����ϰ� �˴ϴ�.
	
	void foo() { } //goo(); // 2

	virtual void goo() { std::cout << "Base::goo" << std::endl; }     // 1
};

struct Derived : public Base
{
	int x = 10; // C++ : �� �ʱ�ȭ ���� ��� Ŭ���� �����ڰ� ���� ȣ��
			    // C# : ��� Ŭ���� ������ ���� �� �ʱ�ȭ�� ���� ����.
	Derived() : x(10) {} // Derived() : Base(), x(10) {}

	virtual void goo() override { std::cout << "Derived::goo : " << x << std::endl; } // 2
};

int main()
{
	Derived d;
	d.foo();   // ��� ������ ������
}

