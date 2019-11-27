// TemplateProgramming.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include <iostream>
#include <type_traits>

using namespace std;

/// static_assert
namespace Static_assert
{
template<typename T>
T gcd(T a, T b)
{
	static_assert(is_integral<T>::value, "error");
	T greatest = 1;
	T bigger = a > b ? a : b;
	for (int i = 2; i < bigger ; ++i)
	{
		if ((a%i == 0) && (b%i == 0))
		{
			greatest = i;
		}
	}

	cout << "Static assert gcd : ";

	return greatest;
}
}	// namespace Static_assert

/// enable_if
namespace Enable_if
{
template<typename T>
typename enable_if<is_integral<T>::value, T>::type gcd(T a, T b)
{
	T greatest = 1;
	T bigger = a > b ? a : b;
	for (int i = 2; i < bigger ; ++i)
	{
		if ((a%i == 0) && (b%i == 0))
		{
			greatest = i;
		}
	}

	cout << "Enable if gcd : ";

	return greatest;
}
}	// namespace Enable_if

int main()
{
	int n1 = 10;
	int n2 = 5;
	short s1 = 10;
	short s2 = 2; 
	double d1 = 3.4;
	double d2 = 1.2;

	{
	using namespace Static_assert;
	cout << gcd(n1, n2) << endl;
	cout << gcd(s1, s2) << endl;
	gcd(3.4, 2.1);
	}

	{
	using namespace Enable_if;
	cout << gcd(n1, n2) << endl;
	cout << gcd(s1, s2) << endl;
	gcd(3.4, 2.1);
	}

	system("pause");
    return 0;
}

