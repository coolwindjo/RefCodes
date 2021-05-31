#include <iostream>
#include <functional>
using namespace std;

// () 를 사용해서 호출하는 것들...
// 1. Function
// 2. Function pointer
// 3. ()를 재정의한 Class
// 4. Lambda expression

#if 0
struct Plus
{
    int operator()(int a, int b) const
    {
        return a + b;
    }
};
#endif

int main()
{
    plus<int> p; 
    int n = p(1, 2);    // p.operator()(1, 2)   // 3
    cout << n <<endl;

    multiplies<int> m;
    cout << m(3, 4) <<endl; // 12

    // a + b;   // a.operator+(b)
    // a - b;   // a.operator-(b)
    // a();     // a.operator()()
    // a(1, 2); // a.operator()(1, 2)

    return 0;
}