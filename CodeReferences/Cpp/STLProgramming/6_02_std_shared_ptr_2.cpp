#include <iostream>
#include <memory>
#include "Car.hpp"
#include "MyAlloc2.hpp"
using namespace std;

void foo( Car* p )
{
    cout << "Delete Car" <<endl;
    delete p;
}
int main()
{
    /*/
    shared_ptr<Car> p(new Car);     // delete
    shared_ptr<Car> p1( new Car, foo );     // delete
    shared_ptr<Car> p2( new Car, [](Car* p){cout<<"[] delete !"<<endl;delete p;} );     // delete
    /*/
    shared_ptr<Car> p3( new Car,
                        [](Car* p){cout<<"[] delete !"<<endl;delete p;},
                        MyAlloc<Car>());     // delete
    //*/

    return 0;
}
