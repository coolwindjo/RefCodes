#include <iostream>
using namespace std;

template<typename T>
void foo(T p)
{
	cout << p.first << ", " << p.second <<endl;
}

#if 0
template<typename T1, typename T2>
pair<T1, T2> make_pair(const T1& a, const T2& b)	// Function template 을 쓰자! (Class template은 template 인자를 생략X => too strict!)
{
	return pair<T1, T2>(a, b);
}
#endif

int main() 
{
	pair<int, double> p1(1, 3.4);
	foo(p1);

	foo(pair<int, int>(1, 1));

	foo(make_pair<int, int>(1, 2));
	foo(make_pair(1, 3));

	foo(pair(1, 4));	// c++17 부터 가능함

	return 0;
}