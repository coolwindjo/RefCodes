#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    using MilliMeter = duration< int, milli >;
    using KiloMeter = duration< int, kilo >;
    using Meter = duration< int, ratio<1,1> >;

    Meter m(600);       // 600 m
    MilliMeter mm(m);   // 60000 : OK.
    /*/
    KiloMeter km(m);    // 0.6  => 0 or 1 : Error!!
    /*/
    KiloMeter km = duration_cast<KiloMeter>(m);    // 0.6  => 0 or 1
    KiloMeter round_km = round<KiloMeter>(m);    // 0.6  => 0 or 1
    KiloMeter floor_km = floor<KiloMeter>(m);    // 0.6  => 0 or 1
    KiloMeter ceil_km = ceil<KiloMeter>(m);    // 0.6  => 0 or 1
    //*/

    cout << mm.count() <<endl;  // 600000
    cout << km.count() <<endl;  // 0
    cout << round_km.count() <<endl;  // 1
    cout << floor_km.count() <<endl;  // 0
    cout << ceil_km.count() <<endl;  // 1

    return 0;
}
