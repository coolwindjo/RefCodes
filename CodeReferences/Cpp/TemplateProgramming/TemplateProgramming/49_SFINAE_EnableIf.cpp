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

/// 정수 계열 인자에 대해서만 사용하고 싶다.
#if 0
template<typename T> void foo(T a)
{
	static_assert(is_integral<T>::value, "error");
}

#else
/// is_integral<T>::value : 정수인지 Check
/// enable_if<T> : enable 되지 않으면 당연히 조건이 맞지 않는 함수로 만들어준다.
template<typename T>
typename enable_if<is_integral<T>::value, void>::type foo(T a)	///< 조건에 맞지 않다면 함수를 생성하지 않음
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