#include <iostream>
#include <type_traits>

// traits 의 종류
// 1. 타입질의 : is_xxx<T>::value
// 2. 변형타입얻기 : xxx<T>::type

// 1. 구조체 템플릿을 만들고 typedef T type을 넣는다.
template<typename T> struct remove_pointer
{
	typedef T type;
};
// 2. 원하는 타입을 얻을수 있도록, 부분 특수화 문법을 통해서
//    "타입을 분할"한다.  "int*" 에서 "int" 와 "*" 를 분리할수 있도록 부분 특수화
template<typename T> struct remove_pointer<T*>
{
	typedef T type;
};

int main()
{
	remove_pointer<int*>::type n; // int

	std::cout << typeid(n).name() << std::endl;
}
