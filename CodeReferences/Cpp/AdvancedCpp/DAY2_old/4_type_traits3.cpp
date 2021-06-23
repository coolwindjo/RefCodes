#include <iostream>

int a;		// 변수 이름 : a    타입 : int
	
int x[3];	// 변수 이름 : x	타입 : int[3]	
							// T[N] : bound array type
							// T[] : unbound array type


template<typename T> struct is_array
{
	static constexpr bool value = false;
	static constexpr int size = -1;
};
template<typename T, int N> struct is_array< T[N] >
{
	static constexpr bool value = true;
	static constexpr int size = N;
};

// C++20 에서는 배열을 인자로 받을때 사용하는 std::span  이라는 아주 좋은 도구가 있습니다.
template<typename T> void foo(const T& a)
{
	//   is_array<int[3]>::value 
	if ( is_array<T>::value )
		std::cout << "배열. 크기는 " << is_array<T>::size  << std::endl;
	else
		std::cout << "배열 아님" << std::endl;
}

int main()
{
	int x[3] = { 1,2,3 };
	foo(x);
}