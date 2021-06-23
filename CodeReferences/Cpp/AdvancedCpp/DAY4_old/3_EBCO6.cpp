#include <iostream>
#include <type_traits>

template<typename T, typename U >
struct PAIR
{
	// C++20 부터 EBCO 기술이 아주 쉬워 졌습니다.
	[[no_unique_address]] T first;
	[[no_unique_address]] U second;

	PAIR() = default;

	template<typename A, typename B>
	PAIR(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}

	T& getFirst() { return first; }
	U& getSecond() { return second; }
};



int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(4);

	// 함수 주소와 삭제자를 같이 보관한다고 생각해 봅시다.

	auto d1 = [](int* p) { delete p; };
	auto d2 = [](int* p) { free(p); };

	PAIR<decltype(d1), int*> pair1(d1, p1);
	PAIR<decltype(d2), int*> pair2(d2, p2);

	// 추후에 삭제가 필요하면
	pair1.getFirst()(pair1.getSecond());

	// 즉, 메모리 주소와 삭제자라는 2가지 정보를 담았지만..
	// 메모리 크기는 4바이트만 사용
	std::cout << sizeof(pair1) << std::endl; // 4

	// C++표준의 unique_ptr 이 내부적으로 우리가 만든
	// PAIR 같은 클래스를 사용합니다.
}

// 평가되지않은 표현식 받아 보세요

