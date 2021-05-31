#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    shared_ptr<Car> sp1(new Car);
    shared_ptr<Car> sp2 = sp1;      // OK. use_count: 2

    unique_ptr<Car> up1(new Car);   // 자원 독점
    /*/
    unique_ptr<Car> up2 = up1;      // error!
    /*/
    unique_ptr<Car> up2 = move(up1);
    //*/

    cout << sizeof(sp1) <<endl;
    cout << sizeof(up1) <<endl;

    return 0;
}