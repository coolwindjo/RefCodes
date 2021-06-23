#include <iostream>

// SFINAE �� ����Ǵ� ��
// 1. Return type
// 2. �Լ� ����
// 3. Template ����

// template<typename T> typename T::type foo(T a)
// template<typename T> void foo(T a, typename T::type* p = 0)
// template<typename T, typename T::type* p = 0> void foo(T a)

template<typename T> void foo(T a)
{
	typename T::type n;	// 1. SFINAE �� ���� ... Version ����
						// 2. Compile Error
	std::cout << "T" << std::endl;
}
// int::type foo(int a) {....}

void foo(...) { std::cout << "..." << std::endl; }

int main()
{
	foo(3); 
}