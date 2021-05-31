#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "Prints.hpp"
using namespace std;

#if 0
/*/
int foo(int a) {return a + 10;}
/*/
int foo(int a, int b) {return a + b;}
//*/
#else
#include <functional>
#endif

int main()
{
    list<int> s1 = { 1,2,3,4,5 };
    list<int> s2 = { 1,2,3,4,5 };
    list<int> s3 = { 0,0,0,0,0 };

#if 0
    /*/
    transform( begin(s1), end(s1), begin(s2), foo );
    /*/
    transform( begin(s1), end(s1), begin(s2), begin(s3), foo );
    //*/
#else
    /*/
    transform( begin(s1), end(s1), begin(s2), begin(s3), multiplies<int>() );
    /*/
    transform( begin(s1), end(s1), begin(s2), begin(s3), [](int a, int b){return a+b;} );
    //*/
#endif

    show(s3);   // 2, 4, 6, 8, 10
                // 1, 4, 9, 16, 25

    return 0;
}