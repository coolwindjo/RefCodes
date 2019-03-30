#include <iostream>

using namespace std;


/// Int to Type: Compile time 에 결정된 int 형태의 상수를 type 으로 만드는 도구
template<int N>
struct Int2Type { static constexpr int value = N; };

/// Int2Type을 발전 시킨 C++11의 새로운 Template
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

/// C++11 에 있는 Traits	=> Inheritance concept 추가...
template<typename T>
struct IsPointer : FalseType {};
template<typename T>
struct IsPointer<T*> : TrueType {};

/// STL 사용
#include <type_traits>	///< C++11의 integral_constant, true_type, false_type

/// Function overloading: Compile time 이름 변경; function 선택의 결정은 Compile time 에 done.
/// Lazy Instantiation 이용
template<typename T>
//void print_imp(const T& a, Int2Type<1> )		///< Pointer 인 경우만 사용할 Template	- print_imp_YES
//void print_imp(const T& a, IntegralConstant<int, 1> )
//void print_imp(const T& a, TrueType )
void print_imp(const T& a, true_type )
{
	cout << "This is a Pointer." << endl;
	cout << a << " : " << *a << endl; 
}
template<typename T>
//void print_imp(const T& a, Int2Type<0>)		///< Pointer 가 아닌 경우 Template	- print_imp_NO
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
	//print_imp(a, IsPointer<T>());	// IsPoint Instance 생성
	print_imp(a, is_pointer<T>());	// IsPoint Instance 생성
#if 0
	/// if 문은 Run time 분기문이므로, Compile time 에는 양 분기 모두 Compile 한다.
	if (IsPointer<T>::value)	///< If (false).
	{
		print_pointer(a);	///< if 문이 false 이므로, 이 Template 은 사용되지 않을 것이다.
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
	//foo(1);	///< 0, 1 은 같은 Type(int)... foo(0), foo(1) 같은 함수 호출...

	//Int2Type<0> t0;
	//Int2Type<1> t1;	// 77과 78은 같은 Type 이지만, Int2Type<77>과 Int2Type<78>은 다른 Type.

	//foo(t0);
	//foo(t1);	///< t0, t1 은 다른 Type...	foo(t0), foo(t1) 다른 함수 호출...

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