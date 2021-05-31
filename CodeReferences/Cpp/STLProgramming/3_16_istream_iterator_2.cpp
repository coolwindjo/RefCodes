#include <iostream>
#include <iterator>
using namespace std;

int main()
{
    char a = 0;
    char b = 0;
    char c = 0;

    // x\ty\tz
    /*/
    cin >> a;
    cin >> b;
    cin >> c;
    /*/
    a = cin.rdbuf()->sgetc();   // x
    b = cin.rdbuf()->snextc();  // \t
    c = cin.rdbuf()->snextc();  // y
    //*/

    cout << a << ", " << b << ", " << c <<endl;

    return 0;
}