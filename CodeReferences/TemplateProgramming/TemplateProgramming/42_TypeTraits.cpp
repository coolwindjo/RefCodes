#include <iostream>
#include <type_traits>

using namespace std;

template<typename T> void goo(const T& a, false_type) { cout << "This is not a pointer." << endl; }
template<typename T> void goo(const T& a, true_type) { cout << "This is a pointer: " << *a << endl; }

template<typename T> void foo(const T& a)
{
	/// T �� Pointer ���� ���ο� ���� Algorithm �� �����ϰ� �ʹٸ�...
	/// 1. Value Ȯ��
	if (is_pointer<T>::value)
	{
		// ...
		// '*a' �̷� ������ ǥ���ϸ� �ȵ�
	}
	else
	{
		// ...
	}
	/// 2. Function overloading ���
	goo(a, is_pointer<T>());

}

int main()
{
	int n = 3;
	foo(n);
	foo(&n);

	system("pause");
	return 0;
}