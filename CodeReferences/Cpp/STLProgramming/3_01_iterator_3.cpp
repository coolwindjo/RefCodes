#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main()
{
    /*/
    vector v = { 1,2,3,4,5 };
    auto p = begin(v);
    /*/
    list v = { 1,2,3,4,5 };
    auto p = begin(v);  // will not invalidate the iterator
    //*/

    cout << *p <<endl;

    v.resize(100);

    cout << *p <<endl;  // invalidated iterator

    return 0;
}
