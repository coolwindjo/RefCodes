#include <iostream>
#include <set>
#include <functional>
using namespace std;

#if 0
template<
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
        > class set;
#endif

int main()
{
    /*/
    set<int> s;     // RB Tree
    /*/
    set< int, greater<int> > s;     // RB Tree
    //*/

    // s.push_front(10);   // Error!

    s.insert(30);
    s.insert(40);   // < 으로 비교, > 으로 변경 가능
    s.insert(20);
    s.insert(10);
    s.insert(45);
    s.insert(25);

    /*/
    // 선형검색.. => not efficient!
    auto p2 = find( begin(s), end(s), 10);
    /*/
    auto p2 = s.find(10);   // binary search
    //*/

    cout << *p2 <<endl;

    auto p = begin(s);  // left most node

    // *p = 10;        // Error!

    while (end(s) != p) {
        cout << *p <<endl;
        ++p;
    }

    return 0;
}
