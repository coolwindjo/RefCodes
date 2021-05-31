#include <iostream>
#include <set>
using namespace std;

struct Point
{
    int x;
    int y;
    Point(int a=0, int b=0) : x(a), y(b) {}

#if 1
    // 1. comparison operation overloading
    bool operator<(const Point &p) const {return x<p.x;}
#endif
};

#if 0
// 2. Function Object for comparison
struct PointLess
{
    bool operator()(const Point &p1, const Point &p2) const {return p1.x<p2.x;}
};
#endif

int main()
{
    // /*/
    set<Point> s;
    /*/
    set<Point, PointLess> s;
    //*/

    s.insert( Point(1, 1) );
    s.emplace(2,2); // < 연산 필요
    s.emplace(3,3);

    s.emplace(2,2);     // ==
                        // if (new_elem < old_elem) left
                        // else if (old_elem < new_elem) right
                        // else 같아고 생성

    auto p = s.find( Point(3,3) );   // ==

    cout << p->x << ", " << p->y <<endl;

    return 0;
}
