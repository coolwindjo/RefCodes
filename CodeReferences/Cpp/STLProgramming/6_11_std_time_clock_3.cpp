#include <iostream>
#include <chrono>
#include <string>
using namespace std;
using namespace chrono;

int main()
{
    system_clock::time_point tp = system_clock::now();

    nanoseconds ns = tp.time_since_epoch();     // 1979-01-01-00-00

    cout << ns.count() <<endl;

    hours h = duration_cast<hours>(ns);
    cout << h.count() <<endl;

    // time_point => string
    time_t t = system_clock::to_time_t(tp);     // time type of C
    string s = ctime(&t);
    cout << s <<endl;

    return 0;
}
