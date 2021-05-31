#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    shared_ptr<Car> p1( new Car );  // 1

    p1->Go();       // Car 의 Member 접근

    Car* p = p1.get();
    cout << p <<endl;

    shared_ptr<Car> p2 = p1;        // 2
    cout << p1.use_count() <<endl;  // 2

    // p1 = new Car;   // error!
    p1.reset( new Car );    // OK
    p1.reset();
    p1.swap(p2);

    return 0;
}
