#include <iostream>
#include <type_traits>

// �ִ����� ���ϱ�.

// enable_if<true, Ÿ��>::type   => "Ÿ��"
// enable_if<false, Ÿ��>::type  => ::type �� ����. 

template<typename T>
typename std::enable_if< std::is_integral_v<T>, T>::type // T�� �����̸� ��ȯŸ�� "T"
											// T�� ������ �ƴϸ� "::type" ����.
gcd(T a, T b)
{
	return 0;
}

double gcd(double a, double b) { std::cout << "double" << std::endl; return 0; }

int main()
{
	gcd(6, 9);
	gcd(3.1, 5.4);
	gcd(3.4f, 1.2f); // 1. template ���� �õ� - ����.. SFINAE �� ���� ������ �ƴ�.
					 // 2. gcd(double, double)���� ���.
}