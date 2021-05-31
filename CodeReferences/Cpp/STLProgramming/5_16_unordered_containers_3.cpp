#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

struct Point
{
    int x, y;
    Point(int a=0, int b=0) : x(a), y(b) {}

    bool operator<(const Point &rhs) const {return x<rhs.x;}
};

// Point의 hash function object
struct PointHash
{
    size_t operator()(const Point &p) const 
    {
        hash<int> hi;
        return hi(p.x) + hi(p.y);
    }
};

struct PointEqual
{
    bool operator()(const Point &p1, const Point &p2) const {return (p1.x==p2.x)&&(p1.y==p2.y);}
};

int main()
{
    /*/
    set<Point> s;           // <  필요, == 는 필요없음
    /*/
    unordered_set<Point, PointHash, PointEqual> s; // hash<int> O, hash<Point> X
    //*/

    s.insert(Point(1,1));   // hash 함수에 전달
    s.emplace(2,2);         // == 도 필요하다!
    s.emplace(3,4);

    s.find(Point(1,1));

    return 0;
}