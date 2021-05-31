#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;

int main()
{
    ifstream f("3_16_istream_iterator_3.cpp");
    
    /*/
    istream_iterator<char> p1(f), p2;       // skip spaces
    /*/
    istreambuf_iterator<char> p1(f), p2;
    //*/
    ostream_iterator<char> p3(cout);

    /*/
    *p3 = *p1;                              // one letter
    /*/
    copy(p1, p2, p3);                       // whole file
    //*/

    return 0;
}