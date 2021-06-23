#include <iostream>
#include <type_traits>

// boost ���̺귯�� �ȿ� �ִ� "compressed_pair" �� ���� �Դϴ�.

class Empty {};

// �Ʒ� PAIR �� �ᱹ �κ� Ư��ȭ �����鸸 ���ǰ� �˴ϴ�.
// �� ��� "primary ����"�� ���� �����ص� �˴ϴ�.
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
