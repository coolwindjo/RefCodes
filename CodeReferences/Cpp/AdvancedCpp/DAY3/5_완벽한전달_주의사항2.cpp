// 9_�Ϻ�������_���ǻ���
#include <iostream>

template<typename F, typename T>
void chronometry(F f, T&& arg)
{
	f(std::forward<T>(arg));
}
void foo() {}
void foo(int a) {}
void foo(int a, int b) {}

int main()
{
	// ���� �̸��� �Լ��� ������ ������.. ���� ȣ���� ���� �����ϴ�.
	foo();
	foo(1);
	foo(1, 2);

//	chronometry(&foo, 1); // error
//	printf("%p\n", &foo); // error

	chronometry(static_cast<void(*)(int)>(&foo), 1); //  ok

}









