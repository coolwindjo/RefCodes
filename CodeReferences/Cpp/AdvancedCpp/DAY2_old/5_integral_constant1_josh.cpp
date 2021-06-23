#include <iostream>
#include <type_traits>

// Pointer인 경우와, 
template<typename T> void printv_pointer(const T& v)
{
	std::cout << v << ":" << *v << std::endl;	// 그래도 Error 남!
}

// Pointer가 아닌 경우로 분리
template<typename T> void printv_not_pointer(const T& v)
{
	std::cout << v << std::endl;
}

template<typename T> void printv(const T& v)
{
	if (std::is_pointer_v<T>)
	{
		printv_pointer(v);
	}
	else
	{
		printv_not_pointer(v);
	}
}

int main()
{
	int n = 10;
	printv(n);
}
