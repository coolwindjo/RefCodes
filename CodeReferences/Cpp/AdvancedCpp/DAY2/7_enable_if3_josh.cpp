#include <iostream>
#include <type_traits>

// GCD 최대공약수 구하기
template<typename T>
// std::enable_if< std::is_integral_v<T>, T >::type	// Error! typename 필요
typename std::enable_if< std::is_integral_v<T>, T >::type	// T 가 정수면, Return type은 "T"
// std::enable_if_t< std::is_integral_v<T>, T >		// T 가 정수면, Return type은 "T"
													// T 가 정수가 아니면, "::type" 없음
gcd(T a, T b)
{

	return 0;
};

double gcd(double a, double b) {std::cout << "double" << std::endl; return 0;}

int main()
{
	gcd(6, 9);
	gcd(3.1, 5.4);

	gcd(3.4f, 1.2f);	// 1. template version 시도 - 실패! SFINAE 에 의해 Error는 아님
						// 2. gcd(double, double) version 사용
}