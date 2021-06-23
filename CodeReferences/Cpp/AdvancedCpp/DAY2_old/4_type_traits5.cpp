// remove_all_pointer
#include <iostream>
#include <type_traits>

// 4�� �����ؼ� 5�� ���弼��.

template<typename T> struct remove_all_pointer
{
	typedef T type;
};

template<typename T> struct remove_all_pointer<T*> // int** *
{													// int* *
													// int  *
	typedef typename remove_all_pointer<T>::type   type;
};


int main()
{
//	remove_pointer<int***>::type n; // int**

	remove_all_pointer<int***>::type n; // int

	std::cout << typeid(n).name() << std::endl;
}




