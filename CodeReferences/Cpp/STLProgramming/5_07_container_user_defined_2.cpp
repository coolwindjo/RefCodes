#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::rel_ops;   // for >, !=

#if 0
namespace std
{
    namespace rel_ops   // relation operators
    {
        template<typename T>
        bool operator>(const T &lhs, const T &rhs) {return !(lhs<rhs);}
        template<typename T>
        bool operator!=(const T &lhs, const T &rhs) {return !(lhs==rhs);}
    }
}

#endif

class Point
{
private:
    int x;
    int y;
public:
    // No default constructor
    Point(int a, int b) : x(a), y(b) {}

    // < 와 == 를 제공한다.
    /*/
    bool operator<(const Point &p) {return x<p.x;}      // Error : const!
    bool operator==(const Point &p) {return x==p.x;}    // Error : const!
    /*/
    bool operator<(const Point &p) const {return x<p.x;}
    bool operator==(const Point &p) const {return x==p.x;}
    //*/

};

int main()
{
    Point p1(1,1);
    Point p2(2,2);

    p1 == p2;
    p1 < p2;

    p1 > p2;
    p1 != p2;

    return 0;
}