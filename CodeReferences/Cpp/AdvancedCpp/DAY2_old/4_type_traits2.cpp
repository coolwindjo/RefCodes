#include <iostream>

// is_pointer �����
// 1. ����ü ���ø��� ����� false ����( value = false ��� �ǹ�.)
// 2. ������ �����ϴ� �κ� Ư��ȭ ������ ����� true ����( value = true )��� �ǹ�.
template<typename T> struct is_pointer
{
//	bool value = false;
//	enum { value = false }; // C++11 �� ������ ������ �׻� �̷��� ��������ϴ�.
	static constexpr bool value = false; // C++11 ���ʹ� "static constexpr" ���� ���
};

template<typename T> struct is_pointer<T*>
{
	//enum { value = true };
	static constexpr bool value = true;
};

template<typename T> void foo(const T& a)
{
	if ( is_pointer<T>::value )
		std::cout << "������" << std::endl;
	else
		std::cout << "������ �ƴ�" << std::endl;
}

int main()
{
	int n = 0;
	foo(n);
	foo(&n);
}