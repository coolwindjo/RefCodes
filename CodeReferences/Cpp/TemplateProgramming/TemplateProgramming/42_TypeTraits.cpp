#include <iostream>
#include <type_traits>

using namespace std;

template<typename T> void goo(const T& a, false_type) { cout << "This is not a pointer." << endl; }
template<typename T> void goo(const T& a, true_type) { cout << "This is a pointer: " << *a << endl; }

template<typename T> void foo(const T& a)
{
	/// T 의 Pointer 인지 여부에 따라 Algorithm 을 변경하고 싶다면...
	/// 1. Value 확인
	if (is_pointer<T>::value)
	{
		// ...
		// '*a' 이런 식으로 표현하면 안됨
	}
	else
	{
		// ...
	}
	/// 2. Function overloading 사용
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