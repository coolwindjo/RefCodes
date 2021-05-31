#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Prints.hpp"
using namespace std;

#if 1
void foo(int &a)
{
    /*/
    cout << a << endl;
    /*/
    a = a*2;
    //*/
}
#endif

struct Show
{
    string sep;
    ostream &os;
    Show(string s = "\n", ostream &o = cout)
        : sep(s), os(o)
    {}
    void operator()(int a) const
    {
        os << a << sep;
    }
};

int main()
{
    vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

    // 1. 일반 함수 전달
    for_each( begin(v), end(v), foo );
    show(v);

    // 2. Function Object 전달
    Show s("\t");
    for_each( begin(v), end(v), s );

    // 3. Lambda expression
    for_each( begin(v), end(v), [](int a){ cout << a <<endl; } );

    return 0;
}