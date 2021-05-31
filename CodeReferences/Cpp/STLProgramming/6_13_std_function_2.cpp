#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

class Test
{
private:
    int data = 0;
public:
    int get_data(void){return data;}
    void f(int a, int b)    // void f( Test* this, int a, int b )
    {
        data = a;
        cout << "f: " << a << ", " << b <<endl;
    }
};

int main()
{
    Test t;

#if 0
    // 1. 일반함수 모양의 function
    function< void(int) > f1;
    f1 = bind(&Test::f, &t, _1, 20);
    f1(10);     // t.f(10,20)
#else
    // 2. 객체를 function 의 인자로 받는 방법
    function< void(Test*, int) > f2;
    f2 = bind(&Test::f, _1, _2, 20);
    f2(&t, 100);     // t.f(100, 20)

    /*/
    function< void(Test, int) > f3;     // pass by value
    f3 = bind(&Test::f, _1, _2, 20);
    f3(t, 200);     // t.f(200, 20)
    /*/
    function< void(Test&, int) > f4;     // pass by reference
    f4 = bind(&Test::f, _1, _2, 20);
    f4(t, 300);     // t.f(300, 20)
    //*/
#endif

    cout << t.get_data() <<endl;    // 10    100

    return 0;
}