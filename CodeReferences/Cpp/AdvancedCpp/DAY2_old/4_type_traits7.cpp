#include <iostream>
#include <type_traits>

template<typename T> void printv(const T& v)
{
	// �Ʒ� �ڵ尡 ������ ������ T�� int �϶� "*v" �� ����Ҽ� �����ϴ�.
	/*
	if ( std::is_pointer_v<T> )     // if ( false )
		std::cout << v << " : " << *v << std::endl;
	else
		std::cout << v << std::endl;
	*/
	// C++17 �� ���ο� if ���� ����ϸ� 
	// Ÿ���� ������ �������� ������ "C++ �ڵ� ����"�� ���� �ʵ��� �Ҽ� �ֽ��ϴ�.
	if constexpr (std::is_pointer_v<T>) 
		std::cout << v << " : " << *v << std::endl;
	else
		std::cout << v << std::endl;
}
// ���ø� ���鶧 ���ǿ� ���� �ٸ� ������ �����ϴ� ����� C++���� 4������ �ֽ��ϴ�.
// 1. integral_constant - C++11 ���
// 2. enable_if           C++11 ��� - C++20 ������ ������ ���� ������ ���
// 3. if constexpr        C++17 ���
// 4. concept ���        C++20 ��� - enable_if �� ������ ����.



int main()
{
	int n = 10;
	printv(n); // 1
//	printv(&n);// 2
}
// �� �� �ڵ尡 ���� �ϱ�� ?



// �����ҽ� ī��(cafe.naver.com/cppmaster) �� �÷� ���ҽ��ϴ�.