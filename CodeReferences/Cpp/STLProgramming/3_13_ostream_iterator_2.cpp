#include <iostream>
#include <iterator>
#include <list>
#include <fstream>
using namespace std;

int main()
{
    ofstream fout("a.txt");
    // /*/
    ostream_iterator<int> oit(fout, ", ");
    /*/
    ostream_iterator<int> oit(fout);    // NULL separated
    //*/

    *oit = 20;
    ++oit;      // no effect
    *oit = 30;  // ((p.operator*()).operator=(30)

    return 0;
}