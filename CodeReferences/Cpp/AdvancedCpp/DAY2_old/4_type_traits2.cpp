#include <iostream>

// is_pointer 만들기
// 1. 구조체 템플릿을 만들고 false 리턴( value = false 라는 의미.)
// 2. 조건을 만족하는 부분 특수화 버전을 만들고 true 리턴( value = true )라는 의미.
template<typename T> struct is_pointer
{
//	bool value = false;
//	enum { value = false }; // C++11 이 나오기 전에는 항상 이렇게 만들었습니다.
	static constexpr bool value = false; // C++11 부터는 "static constexpr" 문법 사용
};

template<typename T> struct is_pointer<T*>
{
	//enum { value = true };
	static constexpr bool value = true;
};

template<typename T> void foo(const T& a)
{
	if ( is_pointer<T>::value )
		std::cout << "포인터" << std::endl;
	else
		std::cout << "포인터 아님" << std::endl;
}

int main()
{
	int n = 0;
	foo(n);
	foo(&n);
}