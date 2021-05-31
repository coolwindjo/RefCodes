#include <iostream>
#include <list>
#include <forward_list>
#include <algorithm>
using namespace std;

int main()
{
    // /*/
    list<int> s = { 1,2,3,4,5,6,7,3,9,10 };
    /*/
    forward_list<int> s = { 1,2,3,4,5,6,7,3,9,10 };
    ssssssssssss/ auto p5 = rbegin(s2);    // single list 에서는 error!
    //*/

    /*/
    auto p1 = begin(s);
    /*/
    list<int>::iterator p1 = begin(s);
    //*/
    list<int>::reverse_iterator p2 = rbegin(s);

    list<int>::const_iterator p3 = cbegin(s);
    // *p3 = 10;       // error!

    list<int>::const_reverse_iterator p4 = crbegin(s);

    auto a1 = begin(s);
    auto a2 = rbegin(s);
    auto a3 = cbegin(s);
    // *a3 = 10;       // error!
    auto a4 = crbegin(s);

    return 0;
}