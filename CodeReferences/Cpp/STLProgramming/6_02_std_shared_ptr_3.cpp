#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    shared_ptr<Car> p1( new Car[10], [](Car* p){delete[] p;} );

    // p1[0].Go();     // Error!   : operator[] X

    /*/
    shared_ptr<Car> p2( new Car[10] );  // bug - delete[], operator[] 없음
    /*/
    shared_ptr<Car[]> p2( new Car[10] );  // delete[], operator[] 있음
    //*/

    p2[0].Go();     // operator[] O 

    return 0;
}
