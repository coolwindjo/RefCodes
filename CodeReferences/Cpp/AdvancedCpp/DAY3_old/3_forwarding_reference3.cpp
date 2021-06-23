#include "cppmaster.h" // vc, g++ ��� ��밡��
//#include <iostream>

template<typename T> void foo(T&& arg)
{
	LOG_FUNCTION_NAME();	// �Ʒ� ��ũ�� ����ؼ� ���

	// __FUNCTION__ : �Լ��̸��� ���� ��ũ��.  C++ ǥ��
	// __FUNCSIG__ : �Լ� �ñ״��ĸ� ��� ��� .  VC ����  g++ �ȵ�.
	// __PRETTY_FUNCTION__ : g++ ����.


	//std::cout << __FUNCTION__ << std::endl;

	//std::cout << __FUNCSIG__ << std::endl;
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
	int n = 10;

	foo(n);  // foo(int&)  �Լ� ����
	foo(10); // foo(int&&) �Լ� ����

	const int c = 10;
	foo(c); 
}




