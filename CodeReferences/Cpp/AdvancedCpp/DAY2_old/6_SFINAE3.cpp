#include <iostream>

// SFINAE �� ����Ǵ� ����
// 1. ��ȯ Ÿ��
// 2. �Լ� ����
// 3. ���ø� ����

//template<typename T> typename T::type foo(T a)
//template<typename T> void foo(T a, typename T::type* p = 0 )
//template<typename T, typename T::type* p = 0> void foo(T a)

template<typename T> void foo(T a)
{
	typename T::type n; // 1. SFINAE �� ���� ... ���� ����
						// 2. ������ ���� => ����..

	std::cout << "T" << std::endl; 
}

void foo(...) { std::cout << "..." << std::endl; }

int main()
{	
	foo(3);  
}