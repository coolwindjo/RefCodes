#include <iostream>
#include <memory>
#include "Car.hpp"
using namespace std;

int main()
{
    /*/
    shared_ptr<Car> wp;     // use count 증가
    /*/
    weak_ptr<Car> wp;     // use count 증가 X
    //*/

    // {
        shared_ptr<Car> sp( new Car );
        wp = sp;
        cout << sp.use_count() <<endl;  // 2    1
    // }   // 대상객체 파괴

    if ( wp.expired() ) {
        cout << "destroyed!" <<endl;
    }
    else {
        cout << "not destroyed!" <<endl;

        // weak_ptr 을 사용해서는 대상객체에 접근할 수 잆다.
        // wp->Go();   // Error: weak_ptr 로 다시 shared_ptr 을 만들어야 한다.
        shared_ptr<Car> sp2 = wp.lock();
        if (nullptr != sp2) {
            sp2->Go();
        }
    }
    return 0;
}
