#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    map<int, string> m;

    m[1] = "One";
    m[0] = "Zero";
    m[2] = "Two";

    auto p = begin(m);      // p는 pair를 가리키는 Pointer

    cout << p->first <<endl;    // 0
    cout << p->second <<endl;    // Zero
    ++p;
    cout << p->first <<endl;    // 1
    cout << p->second <<endl;    // One

    return 0;
}