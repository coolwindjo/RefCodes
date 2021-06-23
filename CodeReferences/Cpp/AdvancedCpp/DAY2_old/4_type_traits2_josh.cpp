#include <iostream>

// is_pointer 만들기
// 1. 구조체 Template을 만들고 false return (value = false) 라는 의미
// 2. 조건을 만족하는 부분 특수화 version을 만들고 true return (value = true) 라는 의미
template<typename T> struct is_pointer
{
	// bool value = false;
	// enum { value = false };
	static constexpr bool value = false; // C++11부터는 "Static constexpr" 문법 사용
};
// template<typename T> struct is_reference<T&>
// template<typename T> struct is_const<const T>
template<typename T> struct is_pointer<T*>
{
	// enum { value = true };
	static constexpr bool value = true;
};

template<typename T> void foo(const T& a)
{
	if ( is_pointer<T>::value )
		std::cout << "Pointer" << std::endl;
	else
		std::cout << "Not a Pointer" << std::endl;
}
int main()
{
	int n = 0;
	foo(n);
	foo(&n);
}