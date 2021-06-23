#include <iostream>
#include <type_traits>

// printv �� ����� 4���� ���

// 1. integral_constant  =>  printv_imp( v, std::is_pointer<T>() )

// 2. enable_if ���  => �Ʒ� �ڵ�
//    C++11�� ǥ�ؿ� �߰��Ǿ�����, �������� ���� ����ϸ� ��.
//    SFINAE  �� C++11�� �ƴ� C++ ó������ �ִ� ����

// 3. if constexpr ( std::is_pointer_v<T> )  - C++17

// 4. concept- c++20

// github.com/aosp-mirror  ����
// platform_system_core �˻� �ϼ���
// libutils/include/utils/typeHelpes.h �������.

// copy_type() �Լ� ã�� ������.






// std::enable_if_t<����, ����Ÿ��>
// ���� Ÿ���� void ��� ���� ����.

template<typename T> 
std::enable_if_t< std::is_pointer_v<T> >
printv(const T& v)
{
	std::cout << "������ �� ���" << std::endl;
}

template<typename T> 
std::enable_if_t< !std::is_pointer_v<T> >
printv(const T& v)
{
	std::cout << "�����Ͱ� �ƴ� ���" << std::endl;
}

int main()
{
//	std::pair<int, double> p;

	int n = 10;
	printv(n);
	printv(&n);

}
