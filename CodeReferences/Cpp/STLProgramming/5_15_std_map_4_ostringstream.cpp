#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    cout << "hello" <<endl; // console out

    ofstream f("a.txt");
    f << "hello";           // file out

    ostringstream oss;
    oss << "hello";         // oss의 buffer out

    string s = oss.str();
    cout << s <<endl;       // "hello"

    int n = 10;
    /*/
    // n의 값을 문자열로...
    char buf[10];
    snprintf(buf, "n = %d", n);
    /*/
    ostringstream oss2;
    oss2 << "n = " << n;

    string s3 = oss2.str();

    cout << s3 <<endl; // n = 10
    //*/

    return 0;
}