// remove_all_pointer
#include <iostream>
#include <type_traits>

// 4번 복사해서 5번 만드세요.

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




