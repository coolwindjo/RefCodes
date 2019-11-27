#include <iostream>
#include <type_traits>

using namespace std;

/// Primary template
template<bool test, typename T = void>
struct Enable_if
{
};
/// Partial specialization
template<typename T>
struct Enable_if<true, T>
{
	typedef T type;
};

/// ���� �迭 ���ڿ� ���ؼ��� ����ϰ� �ʹ�.
#if 0
template<typename T> void foo(T a)
{
	static_assert(is_integral<T>::value, "error");
}

#else
/// is_integral<T>::value : �������� Check
/// enable_if<T> : enable ���� ������ �翬�� ������ ���� �ʴ� �Լ��� ������ش�.
template<typename T>
typename enable_if<is_integral<T>::value, void>::type foo(T a)	///< ���ǿ� ���� �ʴٸ� �Լ��� �������� ����
{
}
#endif

void foo(...) {}

int main()
{
	Enable_if<true, int>::type n1;
	Enable_if<true>::type* n2;
	//Enable_if<false>::type* n3;	///< Error.

	cout << typeid(n1).name() << endl;
	cout << typeid(n2).name() << endl;

	foo(3.5);

	system("pause");
	return 0;
}