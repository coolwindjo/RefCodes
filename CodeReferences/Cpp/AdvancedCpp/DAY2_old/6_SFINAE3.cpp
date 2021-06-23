#include <iostream>

// SFINAE 가 적용되는 곳은
// 1. 반환 타입
// 2. 함수 인자
// 3. 템플릿 인자

//template<typename T> typename T::type foo(T a)
//template<typename T> void foo(T a, typename T::type* p = 0 )
//template<typename T, typename T::type* p = 0> void foo(T a)

template<typename T> void foo(T a)
{
	typename T::type n; // 1. SFINAE 에 의해 ... 버전 실행
						// 2. 컴파일 에러 => 정답..

	std::cout << "T" << std::endl; 
}

void foo(...) { std::cout << "..." << std::endl; }

int main()
{	
	foo(3);  
}