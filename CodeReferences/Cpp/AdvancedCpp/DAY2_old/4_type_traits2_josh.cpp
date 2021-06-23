#include <iostream>

// is_pointer �����
// 1. ����ü Template�� ����� false return (value = false) ��� �ǹ�
// 2. ������ �����ϴ� �κ� Ư��ȭ version�� ����� true return (value = true) ��� �ǹ�
template<typename T> struct is_pointer
{
	// bool value = false;
	// enum { value = false };
	static constexpr bool value = false; // C++11���ʹ� "Static constexpr" ���� ���
};
// template<typename T> struct is_reference<T&>
// template<typename T> struct is_const<const T>
template<typename T> struct is_pointer<T*>
{
	// enum { value = true };
	static constexpr bool value = true;
};

template<typename T> void foo(const T& a)
{
	if ( is_pointer<T>::value )
		std::cout << "Pointer" << std::endl;
	else
		std::cout << "Not a Pointer" << std::endl;
}
int main()
{
	int n = 0;
	foo(n);
	foo(&n);
}