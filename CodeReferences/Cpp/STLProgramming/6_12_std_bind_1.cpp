#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

void f1(int a, int b, int c) {printf("f1: %d, %d, %d\n", a,b,c);}
void f2(int &a)              {a=20;}

int main()
{
    bind(&f1, 1,2,3)();     // bind(callable_object, ...)
                            // : callable_object - function, functor, member method, lambda
    bind(&f1, 1,2,_1)(10);      // f: 1, 2, 10
    bind(&f1, 1,_2,_1)(10, 20); // f: 1, 20, 10

    int n = 0;
    bind(&f2, n)();     // f2(n)
    cout << n <<endl;   // 20? or 0?    : bind by value

    /*/
    reference_wrapper<int> r(n);
    bind(&f2, r)();
    cout << r <<endl;   // 20? or 0?    : bind by reference
    /*/
    bind(&f2, ref(n))();
    cout << n <<endl;   // 20? or 0?    : bind by reference
    //*/

    // bind(&f2, cref(n))(); // Error!: bind by const reference

    return 0;
}