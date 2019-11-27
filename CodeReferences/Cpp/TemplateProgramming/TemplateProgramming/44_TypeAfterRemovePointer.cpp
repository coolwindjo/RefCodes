#include <iostream>
#include <type_traits>

using namespace std;

/*
Type traits �� ����
1. Type �� Ư���� �����ϱ�
2. ��ȯ(������) Type ���ϱ�
*/

/// Primary template: typedef ����
/// Recursive
template<typename T>
struct RemovePointer { typedef T type; };

/// Partial specialization: remove pointer 
/// - ���ϴ� ����� �������� T�� type �� Recursively �����Ѵ�.
template<typename T>	// int** *
struct RemovePointer<T*> { typedef typename RemovePointer<T>::type type; };

template<typename T> 
void foo(T a)
{
	if (is_pointer<T>::value)	///< Type �� Ư�� �����ϱ�
	{
	}

	typename RemovePointer<T>::type n;	///< T ���� pointer�� ������ Type ���� n ����

	cout << typeid(n).name() << endl;
}

int main()
{
	int n = 10;
	foo(&n);

	typename RemovePointer<int***>::type pn;
	cout << typeid(pn).name() << endl;

	system("pause");
	return 0;
}