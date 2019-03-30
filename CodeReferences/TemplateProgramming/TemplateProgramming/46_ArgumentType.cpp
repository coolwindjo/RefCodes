#include <iostream>
#include <type_traits>

using namespace std;

int f(int a, char c) { return 0; }

/// Primary template
template<int N, typename T>
struct Argument;
//{ 
//	//typedef T type; 
//};
/// Partial specialization: ���ϴ� Type �� ���� �� �ֵ��� Type �� ���� �Ѵ�.
template<typename R, typename A1, typename A2>
struct Argument<0, R(A1, A2)> { typedef A1 type; };
template<typename R, typename A1, typename A2>
struct Argument<1, R(A1, A2)> { typedef A2 type; };

template<typename T>	///< T: int(int, char)
void foo(T& a)
{
	typename Argument<0, T>::type n1;	///< int
	typename Argument<1, T>::type n2;	///< char

	cout << typeid(n1).name() << endl;
	cout << typeid(n2).name() << endl;
}

int main()
{
	foo(f);

	system("pause");
	return 0;
}