#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    weak_ptr<Car> wp;

    {
        /*/
        shared_ptr<Car> sp( new Car );
        /*/
        shared_ptr<Car> sp( make_shared<Car>() );
        //*/

        wp = sp;
        cout << "sp.use_count(): " << sp.use_count() <<endl;
    }   // 대상 객체 파괴

    if ( wp.expired() ) {
        cout << "destroyed!" <<endl;
    }
    else {
        // cout << "wp.weak_count(): " << wp.weak_count() <<endl;  // how to check weak count??
    }
    return 0;
}