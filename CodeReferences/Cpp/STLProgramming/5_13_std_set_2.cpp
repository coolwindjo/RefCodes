#include <iostream>
#include <set>
using namespace std;

int main()
{
    /*/
    set<int> s;     // RB Tree
    /*/
    multiset<int> s;     // RB Tree
    //*/

    s.insert(30);
    s.insert(40);
    s.insert(20);
    s.insert(10);
    s.insert(45);
    s.insert(25);

    // /*/
    // set : pair
    // multiset : iterator
    auto ret = s.insert(20);
    /*/
    pair< set<int>::iterator, bool > ret = s.insert(20);
    //*/

#if 0
    if (false == ret.second) {
        cout << "failed!" <<endl;
    }
#endif
    
    for ( auto &n : s ) {
        cout << n <<endl;
    }
    return 0;
}
