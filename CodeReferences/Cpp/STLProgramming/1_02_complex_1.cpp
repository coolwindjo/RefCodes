#include <iostream>
#include <complex>	// Exponential(exp, log, log10), Power(pow, sqrt),
					// Trigonometric(sin, cos, tan, asin, acos, atan),
					// Hyperbolic(sinh, cosh, tanh, asinh, acosh, atanh)
					// cppreference.com 참고

using namespace std;

int main()
{
	complex<double> c1(1, 0);	// double, float, long double 이외의 Type에 대해서는 Unspecified
	cout << c1 <<endl;
	cout << c1.real() <<endl;
	cout << c1.imag() <<endl;

	complex<double> c2 = sin(c1);
	cout << c2 <<endl;

	// complex<int> c3(1, 0);		// 내부적으로 double로 계산되므로 매우 부정확함	
	// complex<int> c4 = sin(c3);	// 내부적으로 double로 계산되므로 매우 부정확함

	complex<double> d(3.2i);
	complex<float> f(3.2if);
	complex<long double> l(3.2il);

	cout << d <<endl;
	cout << f <<endl;
	cout << l <<endl;

	complex<float> c5(3);	// 3, 0
	complex<float> c6(3, 1);	// 3, 1
	complex<float> c7(3if);	// 0, 3

	cout << c5 <<endl;
	cout << c6 <<endl;
	cout << c7 <<endl;

	return 0;
}