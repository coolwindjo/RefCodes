#include <iostream>
#include <memory>
#include "Car.hpp"
#include "MyAlloc2.hpp"
using namespace std;

void* operator new( size_t sz )
{
    cout << "new sz: " << sz <<endl;
    return malloc(sz);
}

int main()
{
#if 0
    shared_ptr<Car> p1( new Car(1,2) );
#else
    #if 0
    shared_ptr<Car> p1 = make_shared<Car>(1,2);
    #else
        #if 0
    shared_ptr<Car> p2(make_shared<Car>());
        #else
    // f( shared_ptr<Car>(new Car), foo() );    // new Car => ahared_ptr<> => foo()
                                                // 이 순서를 기대하지만 표준에 정의되지 않아 보장 X
    // f( make_shared<Car>(), foo() );

    shared_ptr<Car> p1 = allocate_shared<Car>( MyAlloc<Car>() );
        #endif
    #endif
#endif

    return 0;
}
