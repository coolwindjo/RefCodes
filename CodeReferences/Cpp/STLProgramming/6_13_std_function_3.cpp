#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

class Test
{
public:
    int data = 10;
};

int main()
{
    Test t1, t2;

    // 1. 객체 고정 using bind()
    function< int() > f1;   // function 만 <>에 들어갈 수 있음
    f1 = bind(&Test::data, &t1);    // t1.data를 보관

    cout << f1() <<endl;    // t1.data  "getter"

    // f1() = 20;      // t1.data = 20;    Error!

    function< int&() > f2;   // function 만 <>에 들어갈 수 있음
    f2 = bind(&Test::data, &t1);    // t1.data를 보관
    f2() = 20;      // t1.data = 20;

    cout << f2() <<endl;    // t1.data  "getter"

    // 2. 객체를 function 인자로 전달
    function< int&(Test*) > f3;
    f3 = bind(&Test::data, _1);
    f3(&t1) = 30;
    f3(&t2) = 40;

    cout << f3(&t1) <<endl;    // 30
    cout << f3(&t2) <<endl;    // 40

#if 1
    function< int&(Test&) > f4;
    f4 = bind(&Test::data, _1);
    f4(t1) = 50;
#else
    function< int&(Test) > f4;
    f4 = bind(&Test::data, _1); // Error! ????
    f4(t1) = 50;
#endif

    cout << f4(t1) <<endl;    // t1.data  "getter"

    return 0;
}