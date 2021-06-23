#include <iostream>
#include <type_traits>

template<typename T> void printv_imp(const T& v,  YES )
{
	std::cout << v << " : " << *v << std::endl;
}

template<typename T> void printv_imp(const T& v, NO)
{
	std::cout << v << std::endl;
}

template<typename T> void printv(const T& v)
{
	// T이 포인터 여부에 따라 Dispatch( 함수 오버로딩 문법 활용)
	printv_imp(v, std::is_pointer_v<T>  );
				//  T가 포인터     : true (1)
				//  T가 포인터아님 : false (0)
}

int main()
{
	int n = 10;
	printv(n);

}
