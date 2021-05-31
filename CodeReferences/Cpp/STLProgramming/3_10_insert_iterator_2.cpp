#include <iostream>
#include <list>
#include <iterator> // for back_insert_iterator
using namespace std;

#if 0
template<typename T>
back_insert_iterator<T> back_inserter(T& c)
{
    return back_insert_iterator<T>(c);
}
#endif

int main()
{
    int x[5] = { 10,20,30,40,50 };
    list<int> s = { 1,2,3,4,5 };

    copy( x, x+5, begin(s) );   // overwrite

    /*/
    back_insert_iterator< list<int> > p(s);
    copy( x, x+5, p);
    /*/
    copy( x, x+5, back_inserter(s) );
    //*/

    for ( auto &n : s ) {
        cout << n <<endl;
    }

    return 0;
}