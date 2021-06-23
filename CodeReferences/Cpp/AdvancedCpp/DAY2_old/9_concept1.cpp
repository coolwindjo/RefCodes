// 9_concept1
#include <iostream>
#include <type_traits>

// C++20 �� ���鶧 enable_if �� ��ũ���� �ƴ� "����ȭ" �ϰ� �;����ϴ�.
// C++11 ���鶧 ���� "concept" ���� ���.

// g++ 9_concept1.cpp -std=c++20
// cl  9_concept1.cpp /std:c++latest

template<typename T>  requires std::is_pointer_v<T>
void printv(const T& v)
{
	std::cout << "������ �� ���" << std::endl;
}

template<typename T> requires (!std::is_pointer_v<T>)
void printv(const T& v)
{
	std::cout << "�����Ͱ� �ƴ� ���" << std::endl;
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);

}
