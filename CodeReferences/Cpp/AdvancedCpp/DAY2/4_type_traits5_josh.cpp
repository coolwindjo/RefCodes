#include <iostream>
#include <type_traits>

template<typename T> struct remove_all_pointer
{
	typedef T type;
};

template<typename T> struct remove_all_pointer<T*>	// int ** 	*
													// int * 	*
													// int  	*
{
	// typedef remove_all_pointer<T>::type type;	// c++20������ typename ��� ��
	typedef typename remove_all_pointer<T>::type type;
};


int main()
{
	// remove_pointer<int***>::type n;	// int**
	remove_all_pointer<int***>::type n;	// int

	std::cout << typeid(n).name() << std::endl;
}
