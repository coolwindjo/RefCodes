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
    Point(int a, int b) : x(a), y(b) {cout<<"Point()"<<endl;}
    Point(const Point &p) : x(p.x), y(p.y) {cout<<"Point(const Point&)"<<endl;}
    Point(const Point &&p) : x(move(p.x)), y(move(p.y)) {cout<<"Point(const Point&&)"<<endl;}
    virtual ~Point() {cout<<"~Point()"<<endl;}
};

int main()
{
    vector<Point> v;

#if 0
    // 1. 
    Point p1(10,20);
    v.push_back(p1);
#else
    #if 0
    // 2. 임시객체로 넣기
    v.push_back( Point(10,20) );
    #else
        #if 0
    // 3. 객체 자체를 vector가 만들게 한다.
    // 객체를 전달하지 말고, 생성자 인자를 전달한다.
    v.emplace_back( 10,20 );    // emplace_front()
                                // insert() => emplace()
        #else
    Point p1(10,20);    // 객체 생성
    // p1 사용..
    /*/
    v.push_back(p1);
    /*/
    v.push_back( move(p1) );
    //*/
    // p1이 더이상 필요없을 때...
        #endif
    #endif
#endif
    cout << "--------------" <<endl;
    return 0;
}