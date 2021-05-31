#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    /*/
    vector<int> v(10, 0);
    /*/
    vector<int> v = { 1,2,3,1,2,3,1,2,3,1 };
    //*/

    /*/
    v.resize(7);    //?
    /*/
    auto p = remove(begin(v), end(v), 3);    //?
    //*/

    cout << v.size() <<endl;        // 7
    cout << v.capacity() <<endl;    // 10

    /*/
    v.push_back(0);
    /*/
    v.erase(p, end(v));
    //*/
    cout << v.size() <<endl;        // 8
    cout << v.capacity() <<endl;    // 10

    /*/
    v.pop_back();
    cout << v.size() <<endl;        // 7
    cout << v.capacity() <<endl;    // 10

    v.shrink_to_fit();
    cout << v.size() <<endl;        // 7
    cout << v.capacity() <<endl;    // 7

    v.push_back(0);
    cout << v.size() <<endl;        // 8
    cout << v.capacity() <<endl;    // ?
    /*/

    return 0;
}