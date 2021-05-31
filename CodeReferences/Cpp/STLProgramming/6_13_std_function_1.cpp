#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

void f1(int a)              {printf("f1: %d\n", a);}
void f2(int a, int b, int c){printf("f2: %d, %d, %d\n", a,b,c);}

int main()
{
    /*/
    void(*f)(int) = &f1;
    // void(*f)(int) = &f2;    // Error!
    /*/
    function< void(int) > f;
    //*/

    f = &f1;    // OK
    f(10);      // f1(10)

    /*/
    f = &f2;    // Error
    /*/
    // bind(&f2, 1, 2, _1)(10);    // f2(1,2,10)
    f = bind(&f2, 1, 2, _1);
    f(10);      // f2(1,2,10)
    //*/
    
    return 0;
}