#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main()
{
    /*/
    list s1 = { 1,2,3 };    // error for i = i + 2
    /*/
    vector s1 = { 1,2,3 };
    //*/
    auto i = begin(s1);

    int n = *i; // input
    *i = 20;    // output

    ++i;        // ok
    i = i + 2;  // vector, deque: ++i x 2 와 동일하다. list: error!

    return 0;
}