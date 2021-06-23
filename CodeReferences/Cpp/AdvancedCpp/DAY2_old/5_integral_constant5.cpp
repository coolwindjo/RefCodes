#include <iostream>

// C++11 표준 만들때 int2type을 발전 시켜서 아래 템플릿을 제공합니다.
/*
template<typename T, T N> struct integral_constant
{
	static constexpr T value = N;
};

// 아래 3줄에서 모든 변수는 다른 타입 입니다.
integral_constant<int, 0> n0;
integral_constant<int, 1> n1;
integral_constant<short, 0> s0;

// C++11 핵심.
// true/false : 참거짓을 나타내는 "값" 같은 타입.
// true_type, false_type : 참거짓을 나타내는 타입.
typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true>  true_type;

//------------------------------------
// is_pointer를 만들때 아래 처럼 만들었습니다.
template<typename T> struct is_pointer     : false_type {};  // value = false
template<typename T> struct is_pointer<T*> : true_type {};   // value = true
*/

#include <type_traits> // 위 코드가 여기에 있습니다.


template<typename T> void printv_imp(const T& v, std::true_type ) { std::cout << v << " : " << *v << std::endl; }
template<typename T> void printv_imp(const T& v, std::false_type ) { std::cout << v << std::endl; }


template<typename T> void printv(const T& v)
{
	printv_imp(v, std::is_pointer<T>() );

}

int main()
{
	int n = 10;
	printv(n);
	printv(&n);
}
