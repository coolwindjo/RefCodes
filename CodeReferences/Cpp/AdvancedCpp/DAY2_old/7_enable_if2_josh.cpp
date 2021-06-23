#include <iostream>
#include <type_traits>

// GCD 최대공약수 구하기
template<typename T> T gcd(T a, T b)
{
	// static_assert: 조건에 만족하지 않으면 무조건 Error 발생
	static_assert(std::is_integral_v<T>, "not an integer");

	return 0;
};

double gcd(double a, double b) {std::cout << "double" << std::endl; return 0;}

int main()
{
	gcd(6, 9);
	gcd(3.1, 5.4);

	gcd(3.4f, 1.2f);	// float... => template version 사용... compile error 발생
}