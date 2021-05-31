#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
#if 0
    using seconds = duration<int>; // duration< int, ratio<1,1> >;
    using minutes = duration< int, ratio<60,1> >;
    using hours = duration< int, ratio<3600> >;
    using milliseconds = duration< int, milli >;
#endif

    hours h(1);
    minutes m(h);
    seconds s(h);

    cout << m.count() <<endl;   // 60
    cout << s.count() <<endl;   // 3600

    /*/
    hours h2(s);    // Error! : data loss
    /*/
    hours h2 = duration_cast<hours>(s);
    //*/
    cout << h2.count() <<endl;  // 1

    using days = duration< int, ratio<3600*24, 1> >;
    days d(1);
    minutes m2(d);

    cout << m2.count() <<endl;  // 60*24 = 1440

    return 0;
}
