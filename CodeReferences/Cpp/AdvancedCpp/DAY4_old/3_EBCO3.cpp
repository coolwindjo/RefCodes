#include <iostream>
#include <type_traits>

class Empty {};

/*
template<typename T, typename U > 
struct PAIR
{
	T first;
	U second;

	PAIR() = default;

	template<typename A, typename B> 
	PAIR(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}

	T& getFirst()  { return first; }
	U& getSecond() { return second; }
};
*/
template<typename T, typename U >
struct PAIR : public T
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
//	PAIR<int, int> p1;
//	std::cout << sizeof(p1) << std::endl; // 8

	PAIR<Empty, int> p2;
	std::cout << sizeof(p2) << std::endl; // 8
									// 4


}
