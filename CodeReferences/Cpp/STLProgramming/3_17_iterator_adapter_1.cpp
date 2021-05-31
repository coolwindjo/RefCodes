#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<int> s = { 1,2,3,4,5,6,7,3,9,10 };

    auto p1 = begin(s);
    auto p2 = end(s);

    /*/
    auto ret = find(p1, p2, 3);
    /*/
    reverse_iterator< list<int>::iterator > p3(p2); // p3와 p2는 다른 객체
    reverse_iterator< list<int>::iterator > p4(p1);

    auto ret1 = find(p1, p2, 3);
    auto ret2 = find(p3, p4, 3);    // rfind(p1, p2, 3)

    cout << *p3 <<endl;     // 10

    ++p3; // 마치 --p2 처럼 동작

    cout << *p3 <<endl;     // 9
    ++p3;
    cout << *p3 <<endl;     // 3
    ++p3;
    cout << *p3 <<endl;     // 7
    --p2;
    cout << *p2 <<endl;     // 10
    //*/

    return 0;
}