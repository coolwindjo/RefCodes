#include <iostream>
#include <type_traits>

// 최대공약수 구하기.
template<typename T> T gcd(T a, T b)
{
	// 	static_assert : 조건을 만족하지 않으면 무조건 에러 발생..

	static_assert( std::is_integral_v<T>, "not integer");

	return 0;
}

double gcd(double a, double b) { std::cout << "double" << std::endl; return 0;  }

int main()
{
	gcd(6, 9);

	gcd(3.1,  5.4);

	gcd(3.4f, 1.2f); // float... => template 버전 사용.... 컴파일 에러 발생..!!
}