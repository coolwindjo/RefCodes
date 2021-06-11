#include <iostream>
#include <ratio>
using namespace std;

int main()
{
    ratio_add< ratio<1,4>, ratio<2,4> > r2; // 3/4
    cout << r2.num <<endl;   // 3
    cout << r2.den <<endl;   // 4

    ratio<1, 1000> r3;      // milli
    ratio<1000, 1> r4;      // kilo

    milli m;
    kilo k;
    cout << m.den <<endl;   // 1000
    cout << k.num <<endl;   // 1000

    /*
    typedef ratio<1, 1000000000000000000LL> atto;
    typedef ratio<1, 1000000000000000LL> femto;
    typedef ratio<1, 1000000000000LL> pico;
    typedef ratio<1, 1000000000> nano;
    typedef ratio<1, 1000000> micro;
    typedef ratio<1, 1000> milli;
    typedef ratio<1, 100> centi;
    typedef ratio<1, 10> deci;
    typedef ratio<10, 1> deca;
    typedef ratio<100, 1> hecto;
    typedef ratio<1000, 1> kilo;
    typedef ratio<1000000, 1> mega;
    typedef ratio<1000000000, 1> giga;
    typedef ratio<1000000000000LL, 1> tera;
    typedef ratio<1000000000000000LL, 1> peta;
    typedef ratio<1000000000000000000LL, 1> exa;
    */

    return 0;
}
