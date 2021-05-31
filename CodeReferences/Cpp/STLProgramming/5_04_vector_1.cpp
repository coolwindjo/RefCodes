#include <iostream>
#include <vector>
#include <algorithm>
#include "Prints.hpp"
using namespace std;

int main()
{
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 3);
    vector<int> v4(v3);

    // the same
    vector<int> v5 = { 1,2,3,4 };
    vector<int> v6{ 1,2,3,4 };

    // different
    vector<int> v7(6, 0);  // { 0, 0, 0, 0, 0, 0 }
    vector<int> v8{6, 0};  // { 6, 0 }

    //----------------------------------------------
    vector<int> v;
    /*/
    v.push_front(10);    // error!
    /*/
    v.push_back(10);
    //*/
    v.push_back(20);
    v.insert( begin(v)+1, 30 ); 

    show(v);   // 10, 30, 20

    // 요소 꺼내기
    int n = v.front();
    int n1 = v[0];

    int x[5] = { 1,2,3,4,5 };

    v.assign( x, x+5 );     // member method of the container

    show(v);    // 1, 2, 3, 4, 5

    sort( begin(v), end(v) );   // from <algorithm>

    // v[100] = 10;     // no exception! => runtime error!!
    // v.at(100) = 10;  // exception occurs!

    for (int i=0; i<v.size(); ++i){
        v[i] = 10;      // ok
        // v.at(i) = 10;   // not efficient!
    }

    show(v);    // 10, 10, 10, 10, 10
#if 0


#endif

    return 0;
}