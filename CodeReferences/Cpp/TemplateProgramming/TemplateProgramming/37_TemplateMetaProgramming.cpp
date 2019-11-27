#include <iostream>

using namespace std;

/*
Meta function: used in Compile time
C++ Template Meta Programming
*/

template<int N>
struct Factorial
{
	enum { value = N * Factorial<N - 1>::value };
};

/// N == 1 일때를 위한 Specialization
template<>
struct Factorial<1>
{
	enum { value = 1 };
};

int main()
{
	int n = Factorial<5>::value;	// int n = 120;
			// 5 *	F<4>::value
			//		4 *	F<3>::value
			//			3 * F<2>::value
			//				2 * F<1>::value
			//					1 * F<0>::value
	cout << n << endl;

	system("pause");
	return 0;
}