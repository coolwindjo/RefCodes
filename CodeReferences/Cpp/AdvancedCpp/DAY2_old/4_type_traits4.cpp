#include <iostream>
#include <type_traits>

// traits �� ����
// 1. Ÿ������ : is_xxx<T>::value
// 2. ����Ÿ�Ծ�� : xxx<T>::type

// 1. ����ü ���ø��� ����� typedef T type�� �ִ´�.
template<typename T> struct remove_pointer
{
	typedef T type;
};
// 2. ���ϴ� Ÿ���� ������ �ֵ���, �κ� Ư��ȭ ������ ���ؼ�
//    "Ÿ���� ����"�Ѵ�.  "int*" ���� "int" �� "*" �� �и��Ҽ� �ֵ��� �κ� Ư��ȭ
template<typename T> struct remove_pointer<T*>
{
	typedef T type;
};

int main()
{
	remove_pointer<int*>::type n; // int

	std::cout << typeid(n).name() << std::endl;
}
