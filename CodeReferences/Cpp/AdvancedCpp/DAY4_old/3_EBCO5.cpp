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

	T& getFirst() { return first; }
	U& getSecond() { return second; }
};

template<typename T, typename U >
struct PAIR<T, U, true> : public T
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
	int* p1 = new int;
	int* p2 = (int*)malloc(4);

	// 함수 주소와 삭제자를 같이 보관한다고 생각해 봅시다.

	auto d1 = [](int* p) { delete p; };
	auto d2 = [](int* p) { free(p); };

	PAIR<decltype(d1), int*> pair1(d1, p1);
	PAIR<decltype(d2), int*> pair2(d2, p2);

	// 추후에 삭제가 필요하면
	pair1.getFirst()( pair1.getSecond() );

	// 즉, 메모리 주소와 삭제자라는 2가지 정보를 담았지만..
	// 메모리 크기는 4바이트만 사용
	std::cout << sizeof(pair1) << std::endl; // 4

	// C++표준의 unique_ptr 이 내부적으로 우리가 만든
	// PAIR 같은 클래스를 사용합니다.

}
