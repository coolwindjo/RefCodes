#include <iostream>

// ������ ȣ�����
// 1. ��� Ŭ������ ����� ������
// 2. ��� Ŭ������ ������
// 3. �ڽ��� ����� ������
// 4. �ڽ��� ������..

// BaseMember
struct BM	
{
	BM()  { std::cout << "BM()" << std::endl; }
	~BM() { std::cout << "~BM()" << std::endl; }
};
struct DM // DerivedMember
{
	DM() { std::cout << "DM()" << std::endl; }
	~DM() { std::cout << "~DM()" << std::endl; }
};
struct Base
{
	BM bm;
	Base() //   Base() : bm() 
	{
		std::cout << "Base()" << std::endl; 
	}
	~Base() { std::cout << "~Base()" << std::endl; }
};
struct Derived : public Base
{
	DM dm;
	// �Ʒ� �ڵ带 �����Ϸ��� �ּ�ó�� �����մϴ�.
	Derived() // Derived() : Base(), dm()
	{
		std::cout << "Derived()" << std::endl; 
	}
	~Derived() { std::cout << "~Derived()" << std::endl; }
};

int main()
{
	Derived d; // �� ������ ����� ������ ������.
}
