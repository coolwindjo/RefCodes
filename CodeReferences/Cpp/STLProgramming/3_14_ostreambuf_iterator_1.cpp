#include <iostream>
#include <iterator>
using namespace std;

int main()
{
    /*/
    ostream_iterator<int> oit(cout, ", ");
    /*/
    ostreambuf_iterator<char> oit(cout);  // wchar_t
    //*/

    *oit = 65;  // 'A'

    return 0;
}