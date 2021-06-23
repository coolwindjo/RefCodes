#include <iostream>
#include <type_traits>

template<int N> struct int2type
{
	enum { value = N };
};

template<typename T> void printv_imp(const T& v, int2type<1> ) { std::cout << v << " : " << *v << std::endl;}

template<typename T> void printv_imp(const T& v, int2type<0> )  { std::cout << v << std::endl;}


template<typename T> void printv(const T& v)
{
	printv_imp(v, int2type< std::is_pointer_v<T> >() );
					//  int2type<0>
					//  int2type<1>
}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
