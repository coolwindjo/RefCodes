#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

class Test
{
/*/
private:
/*/
public:
//*/
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
    // 객체를 고정하는 경우
    #if 0
    /*/
    bind(&Test::f, &t, 1, 2)();     // t.f(1,2)
    /*/
    bind(&Test::f, t, 1, 2)();     // t.f(1,2)
    //*/
    #else
    bind(&Test::f, ref(t), 1, 2)();     // t.f(1,2)
    #endif
#else
    // 객체를 인자로 전달하는 경우
    #if 0
    bind(&Test::f, _1, 1, 2)(&t);       // t.f(1,2)
    #else
    bind(&Test::f, _1, 1, 2)(t);       // t.f(1,2) : pass by reference
    #endif
#endif

    bind(&Test::data, &t)() = 10;   // t.data = 10

    cout << t.get_data() <<endl;    // 1    0

    return 0;
}