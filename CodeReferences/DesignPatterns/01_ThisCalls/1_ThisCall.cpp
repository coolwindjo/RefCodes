#include<iostream>

using namespace std;

class Point
{
    int x, y;
public:
    void set(int a, int b)  // void set(Point* const this, int a, int b)
    {
        x = a;              // this->x = a;
        y = b;              // this->y = b;
    }

    static void foo(int a)  // void foo(int a)
    {
        //x = a;      // this->x가 되어야 하는데, this가 없다.
    }
};

int main()
{
    Point::foo(10); // 정적 멤버 함수는 객체 없이 호출가능 하다.
    Point p1, p2;
    p1.set(10, 20); // compiled as "set(&p1, 10, 20)"
                    // push 20
                    // push 10
                    // mov ecx, &p1
                    // call set
    
}