#include <iostream>
#include <vector>
#include <list>
#include <ranges>	// C++20

#if 0
void print_first_element(std::vector<int>& v)
{
	int n = v.front();
	std::cout << n << std::endl;
}
#else
	#if 0
template<typename T>
void print_first_element(std::vector<T>& v)
{
	T n = v.front();
	std::cout << n << std::endl;
}
	#else
// 핵심 1. typename Container::value_type	=> Container가 저장하는 type이 필요할 때 사용
template<typename T>
void print_first_element(T &v)
{
	// ?를 생각해보자
	// T : list<double>
	// T::value_type	=> list<double>::value_type => double

	// raw array를 전달하면 T: int[10]의 형태
	// int[10]::value_type 이 될 수 없으므로 error
	/*/
	typename T::value_type n = v.front();		// C++98 - will be deprecated...
	/*/
	std::ranges::range_value_t<T> n = *std::ranges::begin(v);	// C++20 부터 가능
	//*/
	std::cout << n << std::endl;
}
	#endif
#endif

#if 0
// STL의 원리
// Cotainer가 보관하는 Type을 알고 싶을때가 있다.
template<typename T>
class list
{
public:
	typedef T value_type;	// STL의 설계 핵심

};
list<int> s = {1, 2, 3};
list<int>::valut_type n = s.front();	// int n = s.front();
#endif

int main()
{
#if 0
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
#else
	#if 0 
	std::vector<double> v = { 1,2,3,4,5,6,7,8,9,10 };	// error
	#else
		#if 0
	std::list<double> v = { 1,2,3,4,5,6,7,8,9,10 };	// error
		#else
	int v[10] = { 1,2,3,4,5,6,7,8,9,10 };	// error
		#endif
	#endif
#endif

	print_first_element(v);
}
