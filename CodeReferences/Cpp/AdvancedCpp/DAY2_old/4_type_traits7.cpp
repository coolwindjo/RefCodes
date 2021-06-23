#include <iostream>
#include <type_traits>

template<typename T> void printv(const T& v)
{
	// 아래 코드가 에러인 이유는 T가 int 일때 "*v" 를 사용할수 없습니다.
	/*
	if ( std::is_pointer_v<T> )     // if ( false )
		std::cout << v << " : " << *v << std::endl;
	else
		std::cout << v << std::endl;
	*/
	// C++17 의 새로운 if 문을 사용하면 
	// 타입이 조건을 만족하지 않을때 "C++ 코드 생성"을 하지 않도록 할수 있습니다.
	if constexpr (std::is_pointer_v<T>) 
		std::cout << v << " : " << *v << std::endl;
	else
		std::cout << v << std::endl;
}
// 템플릿 만들때 조건에 따라 다른 구현을 제공하는 방법은 C++에서 4가지가 있습니다.
// 1. integral_constant - C++11 기술
// 2. enable_if           C++11 기술 - C++20 나오기 전까지 가장 유명한 기술
// 3. if constexpr        C++17 기술
// 4. concept 기술        C++20 기술 - enable_if 의 발전된 형태.



int main()
{
	int n = 10;
	printv(n); // 1
//	printv(&n);// 2
}
// 왜 이 코드가 에러 일까요 ?



// 오전소스 카페(cafe.naver.com/cppmaster) 에 올려 놓았습니다.