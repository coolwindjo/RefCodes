// ����1
#include <iostream>
#include <string>
#include <type_traits>

// ���� : try~catch,  throw Ű����.
// noexcept
// 1. Ư�� �Լ��� ���ܰ� �ִ��� ������ �����Ҷ� ��� : noexcept( �Լ�ȣ��� )
// 2. �Լ� ������ ���ʿ� �ٿ��� "�Լ��� ���� ����"�� �˸��� ���
void f1() noexcept
{
	int a = 10;
	a = 20;
}
void f2()
{
	// �� �ȿ��� �߻��ϴ� ��� ���ܸ� catch �� ��Ƽ� ó����
	// �ܺο� �ٽ� throw ���� ���� ���� noexcept�� ����.
	int* p = new int[10]; // �޸� ������ std::bad_alloc �̶�� ���ܰ� throw �˴ϴ�.
	//if (p == 0) {}
	delete[] p;
}
// f3�� ���ܰ� ������� ? ������� ?
//void f3() noexcept // ���ܰ� ����.
//void f3() noexcept(true) // ���ܰ� ����.
//void f3() noexcept(false) // ���ܰ� �ִ�

void f3() noexcept(std::is_nothrow_constructible_v<std::string> && 
		           std::is_nothrow_copy_constructible_v<std::string>)
{
	std::string s1 = "AA";
	std::string s2 = s1;
}

void f4() noexcept( noexcept( f3() ) )
{
	f3();
}

int main()
{
	bool b1 = noexcept( f1() );

	std::cout << b1 << std::endl;
	
	bool b2 = std::is_nothrow_constructible_v<std::string>;
	bool b3 = std::is_nothrow_copy_constructible_v<std::string>;

	std::cout << b2 << std::endl;
	std::cout << b3 << std::endl;
}


