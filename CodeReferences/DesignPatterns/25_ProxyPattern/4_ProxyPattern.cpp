// 3_���Ͻ�3
// ���� �����ڿ��Լ� ICalc.h�� CalcProxy.dll�� �޾ƾ� �մϴ�.
#include <iostream>
#include "..\ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "Calc.h"

int main()
{
    ICalc* pCalc = CreateInstance();

    // ������ ������ ���縦 �𸣰� ����� ������ �� �ֽ��ϴ�.
    cout << pCalc->add(10, 20) << endl;
    cout << pCalc->sub(10, 20) << endl;

    //delete pCalc;       // �����ϸ� �ȵ�  => Reference Counter ������� Object���� �ʿ�

    // dll�� ���� ���� dll�� ����ϴ� �ڵ��� �����Ϸ� ������ �޶�
    // ���� �����Ϸ����� new�� delete�� �ڵ尡 �����Ǿ�� �Ѵ�.
    // -> ���� ��� ��� ��ü ���� ����
    system("pause");
    return 0;
}

