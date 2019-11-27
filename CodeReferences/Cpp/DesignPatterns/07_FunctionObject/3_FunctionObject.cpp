#include <iostream>
using namespace std;

// Function vs. Function Object
// 1) Function은 자신만의 Type이 없다.
//      Signature가 동일한 모든 함수는 같은 Type.

// 2) Function Object는 자신만의 Type이 있다.
//      Signature가 동일하더라도 모든 Function Object는 다른 Type이다.


// 함수 객체 => 함수처럼 사용가능한 객체
struct Plus
{
    int operator() (int a, int b)
    {
        return a + b;
    }
};

int main()
{
    Plus p;
    
    int n = p(10, 20);
    cout << n << endl;

    system("pause");
    return 0;
}