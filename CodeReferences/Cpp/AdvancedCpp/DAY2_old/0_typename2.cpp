#include <iostream>
#include <vector>
#include <ranges> // C++20
#include <list>
// 핵심 : typename 컨테이너::value_type   => 컨테이너가 저장하는 타입이 필요할때 사용

/*
void print_first_element(std::vector<int>& v)
{
	int n = v.front();
	std::cout << n << std::endl;
}
*/
/*
template<typename T>
void print_first_element(std::vector<T>& v)
{
	T n = v.front();
	std::cout << n << std::endl;
}
*/
template<typename T>
void print_first_element( T& v)
{
	// ?를 생각해 보세요.
	// T : list<double>
	// T::value_type   => list<double>::value_type  => double

	// raw array 를 전달하면 T : int[10] 의 모양입니다.
	// int[10]::value_type 이 될수 없으므로 error

	typename T::value_type n = v.front(); // C++98
							 

	std::ranges::range_value_t<T> n = std::front(v); //  C++20 부터 변경됩니다.

	std::cout << n << std::endl;
}
int main()
{
//	std::vector<int>    v = { 1,2,3,4,5,6,7,8,9,10 };
//	std::vector<double> v = { 1,2,3,4,5,6,7,8,9,10 };
//	std::list<double> v = { 1,2,3,4,5,6,7,8,9,10 };
	int v[10] = { 1,2,3,4,5,6,7,8,9,10 };

	print_first_element(v);
}

// STL 의 원리
// 컨테이너가 보관하는 타입을 알고 싶을때가 있었다.
/*
template<typename T> class list
{
public:
	typedef T value_type; // STL의 설계 핵심.
};
list<int> s = { 1,2,3 };
list<int>::value_type n = s.front(); // int n = s.front()
*/




