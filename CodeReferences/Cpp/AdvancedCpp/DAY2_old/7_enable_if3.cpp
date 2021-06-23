#include <iostream>
#include <type_traits>

// 최대공약수 구하기.

// enable_if<true, 타입>::type   => "타입"
// enable_if<false, 타입>::type  => ::type 이 없다. 

template<typename T>
typename std::enable_if< std::is_integral_v<T>, T>::type // T가 정수이면 반환타입 "T"
											// T가 정수가 아니면 "::type" 없음.
gcd(T a, T b)
{
	return 0;
}

double gcd(double a, double b) { std::cout << "double" << std::endl; return 0; }

int main()
{
	gcd(6, 9);
	gcd(3.1, 5.4);
	gcd(3.4f, 1.2f); // 1. template 버전 시도 - 실패.. SFINAE 에 의해 에러는 아님.
					 // 2. gcd(double, double)버전 사용.
}