#include <iostream>

// C++ ǥ�� traits ���� ����
// 1. 1999��~2000��濡 traits ��� �߰�...  enum value = false �� ����� ����
// 2. boost ���̺귯������ ����..
// 3. C++11���� ���� ǥ�ؿ� ����
#include <type_traits>

// C++14 ���� �Ʒ� �ڵ尡 ǥ�ؿ� �߰�
//template<typename T>
//using remove_pointer_t = typename std::remove_pointer<T>::type;

template<typename T> void foo(T a)
{
	// 1. Ÿ���� ���� - 2���� ���
	bool b1 = std::is_pointer<T>::value;
	bool b2 = std::is_pointer_v<T>;

	bool b3 = std::is_abstract<T>::value;
	bool b4 = std::is_abstract_v<T>;

	// 2. ���� Ÿ�� ��� - 2���� ���
	typename std::remove_pointer<T>::type n1;
	std::remove_pointer_t<T> n2; // ���� ����.

	//std::ranges::range_value_t<T> n3; // C++20
}

int main()
{
	int n = 0;
	foo(&n);
}
