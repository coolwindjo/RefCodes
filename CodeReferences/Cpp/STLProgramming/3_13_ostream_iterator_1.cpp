#include <iostream>
#include <iterator>
#include <list>
using namespace std;

int main()
{
    int n = 10;

    cout << n <<endl;

    ostream_iterator<int> oit(cout, ", ");

    *oit = 20;  // cout << 20 << ", ";
    *oit = 30;  // cout << 30 << ", ";

    list<int> s = { 1,2,3 };

    copy( begin(s), end(s), oit );
    fill_n( begin(s), 3, 0 );
    fill_n( oit, 3, 0 );    // 0, 0, 0

    return 0;
}