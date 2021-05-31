#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    int a = 0;  // copy initialization
    int a(0);   // direct initilization
    
    shared_ptr<Car> p = new Car;    // Error!  explicit shared_ptr()
    shared_ptr<Car> p(new Car);     // OK!

    shared_ptr<Car> p1(new Car);    // OK!
    shared_ptr<Car> p2 = p1;        // Resource shared pointers   

    return 0;
}
