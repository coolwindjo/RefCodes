// unevaluated2.cpp
#include <iostream>

// �ٽ� 1. �򰡵��� ���� ǥ���Ŀ� �ִ� �Լ��� ���� ������ ����
//      2. sizeof(�Լ�ȣ���) ���� ��� �Լ��� ȣ��Ǵ��� ���� ����.

int  check(int a);
char check(double d);

int main()
{
	int n = sizeof( check(3.4) );

	std::cout << n << std::endl; // 1
}