#include <iostream>
#include <list>
#include <vector>
#include <forward_list>
#include <algorithm>
using namespace std;

int main()
{
    vector v = { 1,2,3,4,5,6,7,8,9,10 };

    // first, second elements 의 최소 요구 조건?
    auto p = find( begin(v), end(v), 5 );   // input iterator

    reverse( begin(v), end(v) );            // bi-directional iterator

    sort( begin(v), end(v) );               // random access iterator (for Quick sort)

    forward_list f = { 1,2,3 };
    // reverse( begin(f), end(f) );     // error!

    list l = { 1,2,3 };
    // sort( begin(l), end(l) );        // error!
    l.sort();                           // ok!
    // v.sort();                        // error!   no sort() in vector<>
    

    for (auto &n : v) {
        cout << n << ", ";
    }
    return 0;
}
