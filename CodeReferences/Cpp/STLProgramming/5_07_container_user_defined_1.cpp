#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    // No default constructor
    Point(int a, int b) : x(a), y(b) {}

    // < 와 == 를 제공한다.
    bool operator<(const Point &p) const {return x<p.x;}
    bool operator==(const Point &p) const {return x==p.x;}

};

int main()
{
    vector<Point> v1;
    /*/
    vector<Point> v2(10);
    /*/
    vector<Point> v2(10, Point(0,0));
    //*/

    /*/
    v2.resize(20);
    /*/
    v2.resize(20, Point(0,0));
    //*/

    // /*/
    sort( begin(v2), end(v2) ); // 크기 비교 ?
    /*/
    sort( begin(v2), end(v2), [](const Point &a, const Point &b){return a.x>b.x;} ); // 크기 비교 ?
    //*/

    return 0;
}