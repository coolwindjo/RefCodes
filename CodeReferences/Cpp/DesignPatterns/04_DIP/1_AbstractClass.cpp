#include <iostream>
using namespace std;

// Abatract Class란?
// : Pure virtual function이 1개 이상 있는 Class
// : Derived class에게 특정 function을 반드시 만들라고 지시하는 것

class Polygon
{
public:
    virtual void draw() = 0;        // Pure virtual function.
};

class Rect : public Polygon     // draw()의 구현부를 제공하지 않으면 
                                // 역시 추상 클래스다.
{
    virtual void draw()
    {
        return ; 
    } 
};

int main()
{
    //Polygon p;
    Rect r;


    system("pause");
    return 0;
}