#include <iostream>
#include <type_traits>

using namespace std;

int f(int a, char c) { return 0; }

/// Primary template
template<typename T>
struct Result { typedef T type; };
/// Partial specialization: ���ϴ� Type �� ���� �� �ֵ��� Type �� ���� �Ѵ�.
template<typename R, typename A1, typename A2>
struct Result<R(A1, A2)> { typedef R type; };

template<typename T>
void foo(T& a)
{
	typename Result<T>::type n;	///< T: int(int, char)

	cout << typeid(n).name() << endl;
}

int main()
{
	foo(f);

	system("pause");
	return 0;
}