#include <iostream>
using namespace std;

// Function vs. Function Object
// 1) Function�� �ڽŸ��� Type�� ����.
//      Signature�� ������ ��� �Լ��� ���� Type.

// 2) Function Object�� �ڽŸ��� Type�� �ִ�.
//      Signature�� �����ϴ��� ��� Function Object�� �ٸ� Type�̴�.


// �Լ� ��ü => �Լ�ó�� ��밡���� ��ü
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