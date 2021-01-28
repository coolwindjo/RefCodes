// 9_�Ϻ�������_���ǻ���
#include <iostream>

template<typename F, typename T>
void chronometry(F f, T&& arg)
{
	f(std::forward<T>(arg));
}

void foo(int* p) {}

int main()
{
	int n = 0;
	foo(0); // ok.     literal 0�� �����ͷ� �Ͻ��� ��ȯ ������
	foo(n); // error   int �� �����ͷ� ��ȯ �ɼ� ����.

//	chronometry(foo, 0); // error.

	chronometry(foo, nullptr); // ok...

	// nullptr�� Ÿ���� "nullptr_t" Ÿ���Դϴ�.
	nullptr_t arg = nullptr;

	// nullptr_t Ÿ���� ��� ������ Ÿ������ �Ͻ��� ��ȯ �˴ϴ�.
	int* p = arg; // ok

}













