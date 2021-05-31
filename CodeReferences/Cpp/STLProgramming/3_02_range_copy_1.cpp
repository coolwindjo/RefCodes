#include <iostream>
#include <list>
using namespace std;

int main()
{
    list s1 = { 1,2,3 };
    list s2 = { 4,5,6 };

    auto p1 = begin(s1);

    /*/
    auto p2 = end(s2);  // invalid range
    /*/
    auto p2 = end(s1);
    //*/

    //[p1, p2)

    while (p1 != p2) {
        ++p1;
    }

    list<int> s3;
    if (s3.empty()) {}
    if (begin(s3) == end(s3)) {}    // empty range is a valid rnage!

    return 0;
}
