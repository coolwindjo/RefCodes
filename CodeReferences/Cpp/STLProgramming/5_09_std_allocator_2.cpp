#include <iostream>
#include <memory>
#include <vector>
#include "Point.hpp"
using namespace std;

#if 1
#include "MyAlloc2.hpp"
#else
template<typename T>
class MyAlloc
{
private:
    /* data */
public:
    MyAlloc(/* args */) {}
    ~MyAlloc() {}
};
#endif

int main()
{
    vector< Point, MyAlloc<Point> > v;

    v.emplace_back(0,0);

    /*/
    allocator<Point> a;
    /*/
    MyAlloc<Point> a;
    //*/

    Point* p = a.allocate(1);   // memory allocation

    /*/
    a.construct(p, 1, 2);       // call constructor
    a.destroy(p);               // call destructor
    /*/
    allocator_traits<decltype(a)>::construct(a, p, 1, 2);   // (constructor, p, 1, 2)
    allocator_traits<decltype(a)>::destroy(a, p);
    //*/

    a.deallocate(p, 1);         // memory deallocation

    return 0;
}