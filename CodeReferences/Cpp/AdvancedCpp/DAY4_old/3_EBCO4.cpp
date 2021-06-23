#include <iostream>
#include <type_traits>

// boost 라이브러리 안에 있는 "compressed_pair" 의 원리 입니다.

class Empty {};

// 아래 PAIR 를 결국 부분 특수화 버전들만 사용되게 됩니다.
// 이 경우 "primary 버전"은 선언만 제공해도 됩니다.
template<typename T, typename U, bool b = std::is_empty_v<T> >
struct PAIR;

template<typename T, typename U >
struct PAIR<T, U, false>
{
	T first;
	U second;

	PAIR() = default;

	template<typename A, typename B>
	PAIR(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}

	T& getFirst()  { return first; }
	U& getSecond() { return second; }
};

template<typename T, typename U >
struct PAIR<T, U, true>  : public T
{
	U second;

	PAIR() = default;

	template<typename A, typename B>
	PAIR(A&& a, B&& b) : T(std::forward<A>(a)), second(std::forward<B>(b)) {}

	T& getFirst() { return *this; }
	U& getSecond() { return second; }
};

int main()
{
	PAIR<int, int> p1;
	std::cout << sizeof(p1) << std::endl; // 8

	PAIR<Empty, int> p2;
	std::cout << sizeof(p2) << std::endl; // 8
									// 4


}
