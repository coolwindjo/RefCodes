#include <iostream>


void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

// ��Ģ 1. ������ ���纻�� �����Ǹ� �ȵȴ�.
// ��Ģ 2. rvalue ������ lvalue ���� ���� 2���� �����Ѵ�.
// "�Ʒ� �ڵ�� �� �Ѱ��� ������ �ֽ��ϴ�." - main ����
template<typename F> void chronometry(F f, int& arg)
{
	f(arg);
}
template<typename F> void chronometry(F f, int&& arg)
{
	f(arg);
}
int main()
{
	hoo(10); // ok
	chronometry(hoo, 10); // �� �ڵ尡 �ǹǷ�.. �� �͵� �翬�� �Ǿ�� �մϴ�.

	int n = 10;

	chronometry(foo, 10);
	chronometry(goo, n); 

	std::cout << n << std::endl;
}
