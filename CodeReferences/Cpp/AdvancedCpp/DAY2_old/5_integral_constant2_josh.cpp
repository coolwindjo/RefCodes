#include <iostream>
#include <type_traits>

template<typename T> void printv_imp(const T& v, YES)
{
	std::cout << v << ":" << *v << std::endl;
}

template<typename T> void printv_imp(const T& v, NO)
{
	std::cout << v << std::endl;
}

template<typename T> void printv(const T& v)
{
	// T 가 Pointer 여부에 따라 Dispatch
	printv_imp(v, ?);
}
int main()
{
	int n = 10;
	printv(n);
}
