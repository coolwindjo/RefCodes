#include <iostream>
using namespace std;

// 1. Casting is unreasonable (비이성적이다).
// 2. So, 4 Castings of C++ are offered.
//      - static_cast<>(): void* 를 다른 type, 또는 연관성 있는 캐스팅만 허용 (안전한 Casting)
//      - reinterpret_cast<>(): Memory reinterpretation, applicable to almost all cases. (주의해서 사용해야 함)
//      - const_cast<>(): 객체의 상수성, 휘발성 제거
//      - dynamic_cast<>(): RTTI 기술, Down casting 용도

int main()
{
    // static_cast
    int *ps1 = (int*) malloc(sizeof(100));
    int *ps2 = static_cast<int*>(malloc(sizeof(100)));


    // reinterpret_cast
    int n = 0;
    //double* pr1 = &n;
    //double* pr2 = static_cast<double*>(&n);
    double* p3 = reinterpret_cast<double*>(&n);
    *p3 = 3.14;


    // const_cast
    const int c = 10;
    //int* pc1 = &c;
    int* pc2 = const_cast<int*>(&c);
    *pc2 = 20;

    cout << *pc2 << endl;
    cout << c << endl;

    volatile int vn = 10;
    //int* pv1 = &vn;
    int* pv2 = const_cast<int*>(&vn);
    *pc2 = 20;

    cout << *pv2 << endl;
    cout << vn << endl;

    system("pause");

    return 0;
}