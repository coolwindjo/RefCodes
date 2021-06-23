#include <iostream>
#include <type_traits>

// printv 를 만드는 4가지 기술

// 1. integral_constant  =>  printv_imp( v, std::is_pointer<T>() )

// 2. enable_if 기술  => 아래 코드
//    C++11에 표준에 추가되었지만, 그전에도 만들어서 사용하면 됨.
//    SFINAE  는 C++11이 아닌 C++ 처음부터 있던 개념

// 3. if constexpr ( std::is_pointer_v<T> )  - C++17

// 4. concept- c++20

// github.com/aosp-mirror  에서
// platform_system_core 검색 하세요
// libutils/include/utils/typeHelpes.h 열어보세요.

// copy_type() 함수 찾아 보세요.






// std::enable_if_t<조건, 리턴타입>
// 리턴 타입이 void 라면 생략 가능.

template<typename T> 
std::enable_if_t< std::is_pointer_v<T> >
printv(const T& v)
{
	std::cout << "포인터 인 경우" << std::endl;
}

template<typename T> 
std::enable_if_t< !std::is_pointer_v<T> >
printv(const T& v)
{
	std::cout << "포인터가 아닌 경우" << std::endl;
}

int main()
{
//	std::pair<int, double> p;

	int n = 10;
	printv(n);
	printv(&n);

}
