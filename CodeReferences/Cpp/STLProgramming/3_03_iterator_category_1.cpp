#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    /*/
    list v = { 1,3,5,7,9,2,4,6,8,10 };  // error!!
    /*/
    vector v = { 1,3,5,7,9,2,4,6,8,10 };
    //*/

    sort(begin(v), end(v));
    for (auto &n : v) {
        cout << n << ", ";
    }
    return 0;
}