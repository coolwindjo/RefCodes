#include <iostream>
#include <list>
#include <stack>
#include <set>
using namespace std;

struct Point
{
    int x;
    int y;
};

int main()
{
    list<Point> s;
    Point pt;
    s.push_back(pt);

    list<Point>::value_type n;  // Point
    list<Point>::iterator   p;  // iterator

    auto p1 = s.begin();
    auto p2 = begin(s);

    list<int> s2;

    s2.push_back(10);
    s2.push_back(20);
    s2.push_back(30);

    // cout << s.pop_back() <<endl;    // error!
    cout << s2.back() <<endl;    // 30
    s.pop_back();
    cout << s2.back() <<endl;    // 20

    return 0;
}


