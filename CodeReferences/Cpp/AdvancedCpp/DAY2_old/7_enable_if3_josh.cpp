#include <iostream>
#include <type_traits>

// GCD �ִ����� ���ϱ�
template<typename T>
// std::enable_if< std::is_integral_v<T>, T >::type	// Error! typename �ʿ�
typename std::enable_if< std::is_integral_v<T>, T >::type	// T �� ������, Return type�� "T"
// std::enable_if_t< std::is_integral_v<T>, T >		// T �� ������, Return type�� "T"
													// T �� ������ �ƴϸ�, "::type" ����
gcd(T a, T b)
{

	return 0;
};

double gcd(double a, double b) {std::cout << "double" << std::endl; return 0;}

int main()
{
	gcd(6, 9);
	gcd(3.1, 5.4);

	gcd(3.4f, 1.2f);	// 1. template version �õ� - ����! SFINAE �� ���� Error�� �ƴ�
						// 2. gcd(double, double) version ���
}