#include <iostream>

using namespace std;


/// Int to Type: Compile time �� ������ int ������ ����� type ���� ����� ����
template<int N>
struct Int2Type { static constexpr int value = N; };

/// Int2Type�� ���� ��Ų C++11�� ���ο� Template
template<typename T, T N>
struct IntegralConstant { static constexpr T value = N; };

typedef IntegralConstant<bool, true> TrueType;
typedef IntegralConstant<bool, false> FalseType;

#if 0
template<typename T>
struct IsPointer { static constexpr bool value = false; };
template<typename T>
struct IsPointer<T*> { static constexpr bool value = true; };
template<typename T>
struct IsPointer<T* const> { static constexpr bool value = true; };
#endif

/// C++11 �� �ִ� Traits	=> Inheritance concept �߰�...
template<typename T>
struct IsPointer : FalseType {};
template<typename T>
struct IsPointer<T*> : TrueType {};

/// STL ���
#include <type_traits>	///< C++11�� integral_constant, true_type, false_type

/// Function overloading: Compile time �̸� ����; function ������ ������ Compile time �� done.
/// Lazy Instantiation �̿�
template<typename T>
//void print_imp(const T& a, Int2Type<1> )		///< Pointer �� ��츸 ����� Template	- print_imp_YES
//void print_imp(const T& a, IntegralConstant<int, 1> )
//void print_imp(const T& a, TrueType )
void print_imp(const T& a, true_type )
{
	cout << "This is a Pointer." << endl;
	cout << a << " : " << *a << endl; 
}
template<typename T>
//void print_imp(const T& a, Int2Type<0>)		///< Pointer �� �ƴ� ��� Template	- print_imp_NO
//void print_imp(const T& a, IntegralConstant<int, 0> )
//void print_imp(const T& a, FalseType )
void print_imp(const T& a, false_type )
{
	cout << "This is not a Pointer." << endl;
	cout << a << endl;
}

template<typename T> 
void print_value(const T& a)
{
	//print_imp(a, Int2Type<IsPointer<T>::value>());	// print_imp_NO()
	//print_imp(a, IntegralConstant<int, IsPointer<T>::value>());	// print_imp_NO()
	//print_imp(a, IsPointer<T>());	// IsPoint Instance ����
	print_imp(a, is_pointer<T>());	// IsPoint Instance ����
#if 0
	/// if ���� Run time �б⹮�̹Ƿ�, Compile time ���� �� �б� ��� Compile �Ѵ�.
	if (IsPointer<T>::value)	///< If (false).
	{
		print_pointer(a);	///< if ���� false �̹Ƿ�, �� Template �� ������ ���� ���̴�.
	}
	else
	{
		print_not_pointer(a);
	}
#endif
}

int main()
{
	int n = 3;
	double d = 3.3;

	//foo(0);
	//foo(1);	///< 0, 1 �� ���� Type(int)... foo(0), foo(1) ���� �Լ� ȣ��...

	//Int2Type<0> t0;
	//Int2Type<1> t1;	// 77�� 78�� ���� Type ������, Int2Type<77>�� Int2Type<78>�� �ٸ� Type.

	//foo(t0);
	//foo(t1);	///< t0, t1 �� �ٸ� Type...	foo(t0), foo(t1) �ٸ� �Լ� ȣ��...

	print_value(n);	// Used to be an error..
	print_value(d);
	print_value(&n);

	IntegralConstant<int, 0> t0;
	IntegralConstant<int, 1> t1;
	IntegralConstant<short, 1> t2;

	IntegralConstant<bool, true> b1;
	IntegralConstant<bool, false> b2;

	system("pause");
	return 0;
}