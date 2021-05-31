#include <iostream>
#include <memory>
using namespace std;

class Shape {};
class Rect      : public Shape {};
class Circle    : public Shape {};

/*/
Shape* CreateShape(int type)    // Typical Factory Method
/*/
unique_ptr<Shape> CreateShape(int type)    // sp <- up : OK, thus up is more general
//*/
{
    /*/
    Shape* p = nullptr;
    /*/
    // unique_ptr<Shape> p(nullptr);
    unique_ptr<Shape> p;
    //*/
    switch (type) {
        /*/
        case 1: p = new Rect;   break;
        case 2: p = new Circle; break;
        /*/
        case 1: p.reset(new Rect);   break;
        case 2: p.reset(new Circle); break;
        //*/
    }
    return p;
}

int main()
{
    /*/
    Shape* p = CreateShape(1);
    /*/
    unique_ptr<Shape> upShape = CreateShape(1);
    shared_ptr<Shape> spShape = CreateShape(1);
    //*/

    return 0;
}