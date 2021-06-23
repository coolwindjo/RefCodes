#include <iostream>
#include <algorithm>
#include <vector>

// 컨테이너::value_type     => 컨테이너가 저장하는 타입
// 반복자타입::value_type   => 반복자가 가리키는 타입

// std::iter_value_t<반복자타입> => 반복자가 가리키는 타입(C++20, 진짜 포이터도 가능)

//template<typename Iter, typename T > requires std::predicate<T, typename Iter::value_type >
//template<typename Iter, typename T > requires std::predicate<T, typename std::iterator_traits<Iter>::value_type >

template<typename Iter, typename T > requires std::predicate<T, std::iter_value_t<Iter> >
void find(Iter first, Iter last, T value)
{
	std::cout << "조건 검색" << std::endl;
}

template<typename Iter, typename T > requires (!std::predicate < T, std::iter_value_t<Iter> >)
void find(Iter first, Iter last, T value)
{
	std::cout << "값 검색" << std::endl;
}

int main()
{
//	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	int v[10] = { 1,2,3,4,5,6,7,8,9,10 };

//	auto p1 = std::find(   v.begin(), v.end(), 3);
//	auto p2 = std::find_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; } );

//	find(v.begin(), v.end(), 3);
//	find(v.begin(), v.end(), [](int n) { return n % 2 == 0; });

	// v.begin() 보다 std::begin(v) 가 좋습니다.
	// v가 raw 배열이라도 문제 없이 동작합니다.
	find(std::begin(v), std::end(v), 3);
	find(std::begin(v), std::end(v), [](int n) { return n % 2 == 0; });


}

