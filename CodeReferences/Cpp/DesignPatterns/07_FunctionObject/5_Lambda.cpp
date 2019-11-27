#include <iostream>
using namespace std;

//bool cmp1(int a, int b)
inline bool cmp1(int a, int b)
{
    return a > b;
}
//bool cmp2(int a, int b)
inline bool cmp2(int a, int b)
{
    return a < b;
}

#include <algorithm>    // 이미 정책 변경 가능한 sort()가 여기 있습니다.
#include <functional>   // less<>, greater<> 함수 객체가 이 안에 있습니다.

int main()
{
    int x[10] = { 1,3,5,7,9,2,4,6,8,10 };
    // 핵심: sort()의 정책교환인자는 T입니다.

    // 1. 정책으로 함수를 사용할 때,
    // 장점: 정책을 여러번 교체해도 sort()의 기계어는 1 개이다.
    // 단점: 정책이 inline 치환 안 되므로 성능저하가 있다.
    sort(x, x + 10, cmp1);
    sort(x, x + 10, cmp2);

    // 2. 정책으로 함수 객체를 사용할 때,
    // 장점: 정책이 inline 치환 되므로 빠르게 동작
    // 단점: 정책을 교환한 횟수 만큼의 sort() 기계어 코드 생성 => 코드 메모리상의 부하 발생
    less<int> f1; greater<int> f2;
    sort(x, x + 10, f1);    // sort(int*, int*, less<int>)
    sort(x, x + 10, f2);    // sort(int*, int*, greater<int>)

    for (int i = 0; i < 10; ++i)
    {
        cout << x[i] << endl;
    }

    // 람다: 함수 객체를 쉽게 만드는 문법 - 익명의 함수 객체 (Closure)
    // C# : 익명의 Delegate
    // Java : 함수형 interface
    // Obj-C : 블록 프로그래밍
    // 구현 자체가 header file에 있으면 자동으로 inline으로 compile된다.

    // 2008년부터 컴파일러에서 이미 지원하였습니다.
    // - Visual Studio 2010, gcc 4.5
    // 1980: C++탄생
    // 1998: 1차 표준 확정, 2003년 수정판: C++98/08
    // 2011: 2차 표준 확정, 2014년 수정판: C++11/14 - Modern C++
    // 2017: 3차 표준 확정 예정
    struct abs_less
    {
        bool operator()(int a, int b) { return abs(a) > abs(b); }
    };

    abs_less al;
    sort(x, x + 10, al);

    // 람다: 자동으로 inline임
    int n = 20;
    sort(x, x + 10, [n](int a, int b) { return abs(a) > abs(b) + n; });
    for (int i = 0; i < 10; ++i)
    {
        cout << x[i] << endl;
    }

    system("pause");
    return 0;
}