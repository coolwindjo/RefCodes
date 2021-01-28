#include <iostream>
#include <functional>

void goo(int& a) { a = 100;}

// call by value�� ����ϴ� ������ �Լ�
template<typename F, typename T> void Caller(F f, T arg)
{
	f(arg);
}
int main()
{
	int n = 10;

	// Caller(goo, n); // caller �� ���纻�� ����� ������ ����..

	// n �� goo���� ������ �����Ϸ���
//	std::reference_wrapper<int> r(n);
//	Caller(goo, r);

	// ref(n) : reference_wrapper ��ü�� �������ִ� �Լ�.
	Caller(goo, std::ref(n) );


	std::cout << n << std::endl;
}