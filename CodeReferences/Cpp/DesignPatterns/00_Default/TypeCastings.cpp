#include <iostream>
using namespace std;

// 1. Casting is unreasonable (���̼����̴�).
// 2. So, 4 Castings of C++ are offered.
//      - static_cast<>(): void* �� �ٸ� type, �Ǵ� ������ �ִ� ĳ���ø� ��� (������ Casting)
//      - reinterpret_cast<>(): Memory reinterpretation, applicable to almost all cases. (�����ؼ� ����ؾ� ��)
//      - const_cast<>(): ��ü�� �����, �ֹ߼� ����
//      - dynamic_cast<>(): RTTI ���, Down casting �뵵

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