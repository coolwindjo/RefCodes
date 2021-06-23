#include <iostream>

// C++ 표준 traits 사용법 정리
// 1. 1999년~2000년경에 traits 기술 발견...  enum value = false 로 만들던 시절
// 2. boost 라이브러리에서 지원..
// 3. C++11에서 공식 표준에 도입
#include <type_traits>

// C++14 에서 아래 코드가 표준에 추가
//template<typename T>
//using remove_pointer_t = typename std::remove_pointer<T>::type;

template<typename T> void foo(T a)
{
	// 1. 타입의 조사 - 2가지 방식
	bool b1 = std::is_pointer<T>::value;
	bool b2 = std::is_pointer_v<T>;

	bool b3 = std::is_abstract<T>::value;
	bool b4 = std::is_abstract_v<T>;

	// 2. 변형 타입 얻기 - 2가지 방식
	typename std::remove_pointer<T>::type n1;
	std::remove_pointer_t<T> n2; // 위와 동일.

	//std::ranges::range_value_t<T> n3; // C++20
}

int main()
{
	int n = 0;
	foo(&n);
}
