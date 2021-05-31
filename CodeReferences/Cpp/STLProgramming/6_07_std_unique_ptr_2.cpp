#include <iostream>
#include <memory>
using namespace std;

void foo(int* p)
{
    cout << "foo" <<endl;
    delete p;
}

struct Deleter
{
    void operator()(int* p) const
    {
        delete p;
    }
};

int main()
{
    /*/
    shared_ptr<int> sp( new int, foo );
    /*/

#if 0
    // 1. Function Object 사용
    unique_ptr< int, Deleter > up( new int );
#else
    #if 0
    // 2. Function Pointer 사용
    unique_ptr< int, void(*)(int*) > up( new int, foo );
    #else
    // 3. Lambda expression 사용
    auto f = [](int* p){cout<<"[](){delete}"<<endl;delete p;};
    unique_ptr< int, decltype(f) > up( new int, f );

    // 배열 object 관리 할 경우
    unique_ptr<int[]> uparr( new int[10] );
    #endif
#endif
    //*/

    return 0;
}