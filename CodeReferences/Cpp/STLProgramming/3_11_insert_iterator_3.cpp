#include <iostream>
#include <list>
#include <iterator> // for back_insert_iterator
using namespace std;

int main()
{
    int x[5] = { 10,20,30,40,50 };
    list<int> s = { 1,2,3,4,5 };

    /*/
#if 0
    back_insert_iterator< list<int> > p(s);
#else
    #if 0
    front_insert_iterator< list<int> > p(s);     // <iterator> 반드시 필요!
    #else
    insert_iterator< list<int> > p(s, begin(s));    // front_insert_iterator와 다르게 앞단에 정방향 순서로 삽입됨
    #endif
#endif
    copy( x, x+5, p);
    /*/
    copy( x, x+5, back_inserter(s) );       // 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 
    copy( x, x+5, front_inserter(s) );      // 50, 40, 30, 20, 10, 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 
    copy( x, x+5, inserter(s, ++begin(s)) );// 50, 10, 20, 30, 40, 50, 40, 30, 20, 10, 1, 2, 3, 4, 5, 10, 20, 30, 40, 50 
    // --begin(s) : nullptr = end(s) 인 것으로 추정됨
    //*/

    for ( auto &n : s ) {
        cout << n << ", ";
    }

    return 0;
}