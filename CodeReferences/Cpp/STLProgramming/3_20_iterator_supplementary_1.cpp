#include <iostream>
#include <iterator>
#include <forward_list>
using namespace std;

int main()
{
    int x[10] = { 1,2,3,4,5,6,7,8,9,10 };
    forward_list<int> s = { 1,2,3,4,5,6,7,8,9,10 };

    auto p1 = begin(s);

    cout << *p1 <<endl; // 1

    /*/
    auto p2 = ++begin(x);
    /*/
    auto p2 = next(begin(x));
    //*/

    cout << *p2 <<endl; // 2

    advance(p1, 3);   // p1 + 3

    cout << *p1 <<endl; // 4

    cout << distance( begin(s), p1 ) <<endl;    // p1 - begine(x)   => 3

    iter_swap( begin(x), p2);

    cout << *p2 <<endl; // 1

    iter_swap( begin(x), p1);

    cout << *p1 <<endl; // 1

    return 0;
}