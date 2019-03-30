#include <iostream>
#include <type_traits>

using namespace std;

/*
Type traits 의 종류
1. Type 의 특질을 조사하기
2. 변환(연관된) Type 구하기
*/

/// Primary template: typedef 제공
/// Recursive
template<typename T>
struct RemovePointer { typedef T type; };

/// Partial specialization: remove pointer 
/// - 원하는 모양이 나오도록 T의 type 을 Recursively 분할한다.
template<typename T>	// int** *
struct RemovePointer<T*> { typedef typename RemovePointer<T>::type type; };

template<typename T> 
void foo(T a)
{
	if (is_pointer<T>::value)	///< Type 의 특질 조사하기
	{
	}

	typename RemovePointer<T>::type n;	///< T 에서 pointer를 제거한 Type 으로 n 선언

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