#include <iostream>
#include <chrono>
#include <thread>   // for this_thread::sleep_for()
using namespace std;
using namespace chrono;

void foo(seconds s) {}

int main()
{
    // seconds => duration< int, ratio<1,1> >
    seconds s1(3);  // OK : direct iniitialization
    // seconds s2 = 3; // Error : explicit duration()
    seconds s3 = 3s;// OK : using Copy Constructor secondes operator"s(3) (user defined literal)
    seconds s4 = 3min;

    cout << s4.count() <<endl;

    // foo( 3 );    // Error: seconds s = 3
    foo( 3s );      // OK

    cout << "Sleep for 3ns" <<endl;
    this_thread::sleep_for( 3ns );
    cout << "Sleep for 1s" <<endl;
    this_thread::sleep_for( 1s );

    seconds s5 = 3min + 40s;

    cout << s5.count() <<endl;  // 220

    return 0;
}
