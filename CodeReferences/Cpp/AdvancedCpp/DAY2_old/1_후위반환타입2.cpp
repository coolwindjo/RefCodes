#include <iostream>

/*
int Mul(int a, int b)
{
	return a * b;
}
*/

/*
template<typename T> T Mul(T a, T b)
{
	return a * b;
}
*/
template<typename T1, typename T2> 
//decltype( a * b ) Mul(T1 a, T2 b)
auto Mul(T1 a, T2 b) -> decltype(a * b)  // C++11 스타일
//auto Mul(T1 a, T2 b)  // C++14 스타일
{
	return a * b;
}

int main()
{
	std::cout << Mul(1,   3) << std::endl;
	std::cout << Mul(1.1, 3.3) << std::endl;
	std::cout << Mul(1,   3.3) << std::endl;

	int n = 10;
	int& r = n;

//	auto a1 = r;    // auto는 우변의 참조를 버리고 타입 결정. int
//	decltype(r) d1; // d1은 int&. 초기값이 없기 때문에 error.


//	a = 10;
//	int a = 0;
}








