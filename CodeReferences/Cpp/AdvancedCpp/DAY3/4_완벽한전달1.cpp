#include <iostream>

// Perfect fowarding
// "���� ���� ���ڸ� �ٸ� ������ �Ϻ��ϰ� �����ϴ� ���".

void foo(int a)  {}
void goo(int& a) { a = 100; }

// �Լ��� ����ð��� �����ϴ� �Լ�
template<typename F> void chronometry(F f, const int& arg)
{
	// �Լ� ȣ������ �ð� ����
	f(arg); // �Լ� ȣ��
	// �ɸ��ð� ���
}
int main()
{
	int n = 10;

	chronometry(foo, 10); // foo(10);
	chronometry(goo, n);  // goo(n);

	std::cout << n << std::endl;
}
