#include <iostream>
using namespace std;

#if 1
#include <ratio>
#else
// /*/
template<intmax_t _Nx, intmax_t _Dx = 1>
struct ratio
{
    static constexpr intmax_t num = _Nx;
    static constexpr intmax_t den = _Dx;

    typedef ratio<num, den> type;
};
/*/
template<intmax_t _Nx, intmax_t _Dx = 1>
struct ratio
{
	static_assert(_Dx != 0, 			"zero denominator");
	static_assert(-INTMAX_MAX <= _Nx,	"numerator too negative");
	static_assert(-INTMAX_MAX <= _Dx,	"denominator too negative");

	static constexpr intmax_t num =
			_Sign_of<_Nx>::value * _Sign_of<_Dx>::value * _Abs<_Nx>::value / _Gcd<_Nx, _Dx>::value;

	static constexpr intmax_t den =
			_Abs<_Dx>::value / _Gcd<_Nx, _Dx>::value;

	typedef ratio<num, den> type;
};
//*/
#endif

int main()
{
    ratio<2, 4> r1; // 2/4

    cout << sizeof(r1) <<endl;          // 1 : literal size

    cout << r1.num <<endl;              // 1
    cout << r1.den <<endl;              // 2

    cout << ratio<2, 4>::num <<endl;    // 1
    cout << ratio<2, 4>::den <<endl;    // 2

    return 0;
}
