#include <iostream>

// ���� ǥ���İ� �Լ������� ��ȯ

int main()
{
	int(*f)(int, int) = [](int a, int b) { return a + b; };
}