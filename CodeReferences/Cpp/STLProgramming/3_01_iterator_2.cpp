#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main()
{
    /*/
    list s = { 1,2,3,4,5 };
    vector s = { 1,2,3,4,5 };
    /*/
    int s[] = { 1,2,3,4,5 };
    //*/

#if 0
    list<int>::iterator p = s.begin();
#else
    #if 0
        auto p = s.begin();
    #else
        auto p = begin(s);     // C++11 : STL container 와  일반 배열 모두 적용가능
    #endif
#endif

    int n = size(s);    //s.size();
    cout << n <<endl;
    
    auto p2 = end(s);
    // *p2 = 10;   // runtime error!!

    return 0;
}