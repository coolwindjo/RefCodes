#include <iostream>
#include <list>
#include <vector>
#include <iterator>	// for iterator_traits
using namespace std;

#if 0
template<typename T>
struct iterator_traits
{
	using value_type = typename T::value_type;
};

// 핵심: Pointer version을 부분 특수화
template<typename T>
struct iterator_traits<T*>
{
	using value_type = T;
};
#endif

template<typename T>
typename iterator_traits<T>::value_type sum(const T &first, const T &last)
{
	// T : int*
	/*/
	typename T::value_type s = 0;
	/*/
	typename iterator_traits<T>::value_type s = 0;
	//*/

	T it = first;
	while (last != it) {
		s += *it++;
	}

	return s;
}

int main()
{
#if 1
	#if 0
		list<int> s = { 1,2,3,4,5,6,7,8,9,10 };
	#else
		vector<int> s = { 1,2,3,4,5,6,7,8,9,10 };
	#endif
#else
	int s[10] = { 1,2,3,4,5,6,7,8,9,10 };	// error @ sum() : Raw pointer 는 value_type이 없다
#endif
	int n = sum( begin(s), end(s) );	// T: int*

	cout << n << endl;	// 55

	return 0;
}
