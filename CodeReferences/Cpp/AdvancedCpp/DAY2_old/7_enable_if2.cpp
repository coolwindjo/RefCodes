#include <iostream>
#include <type_traits>

// �ִ����� ���ϱ�.
template<typename T> T gcd(T a, T b)
{
	// 	static_assert : ������ �������� ������ ������ ���� �߻�..

	static_assert( std::is_integral_v<T>, "not integer");

	return 0;
}

double gcd(double a, double b) { std::cout << "double" << std::endl; return 0;  }

int main()
{
	gcd(6, 9);

	gcd(3.1,  5.4);

	gcd(3.4f, 1.2f); // float... => template ���� ���.... ������ ���� �߻�..!!
}