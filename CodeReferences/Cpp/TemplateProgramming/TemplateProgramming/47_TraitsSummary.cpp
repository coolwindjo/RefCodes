#include <iostream>

using namespace std;

/// C++14 표준 remove_pointer_t, is_pointer_v
template<typename T> using Remove_pointer_t = typename remove_pointer<T>::type;
template<typename T> using Is_pointer_v = typename is_pointer<T>::value;

template<typename T> void foo_imp(T a, true_type){}
template<typename T> void foo_imp(T a, false_type){}

template<typename T> void foo(T a)
{
	//bool b = is_pointer<T>::value;
	bool b = is_pointer_v<T>;

	/// T 에서 Pointer 를 제거한 Type 구하는 방법
	typename remove_pointer<T>::type n1;
	Remove_pointer_t<T> n2;

	/// T 가 Pointer 인지 조사하는 방법
	bool b1 = is_pointer<T>::value;
	bool b2 = is_pointer_v<T>;

	foo_imp(a, is_pointer<T>());	///< Function overloading 사용
}

int main()
{
	int n = 10;
	foo(&n);

	system("pause");
	return 0;
}