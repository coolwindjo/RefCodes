#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    Car* p = new Car;

    /*/
    shared_ptr<Car> sp1(p);     // 제어 블럭 생성
    shared_ptr<Car> sp2(p);     // 제어 블럭 생성   => 대상 객체가 sp1이 지워지면, 같이 지워질 수 있음!!
    /*/
    shared_ptr<Car> sp3(new Car);   // RAII (Resource Acquision Is Initialization)
    shared_ptr<Car> sp4 = make_shared<Car>();
    //*/

    return 0;
}
