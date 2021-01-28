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
	// typedef remove_all_pointer<T>::type type;	// c++20에서는 typename 없어도 됨
	typedef typename remove_all_pointer<T>::type type;
};


int main()
{
	// remove_pointer<int***>::type n;	// int**
	remove_all_pointer<int***>::type n;	// int

	std::cout << typeid(n).name() << std::endl;
}
