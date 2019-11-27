#include <iostream>
#include <typeinfo>
using namespace std;

// 과제 5. typelist 만들기

// TypeList 는 "Modern C++ Design" 책의 저자인 "Andrei Alexandrescu" 가 만든 "loki" 라이브러리에 있는 코드 입니다.
// 현재 "face book"의 수석 엔지니어로서 페이스북이 사용하는 "C++라이브러리"를 만든 개발자 입니다.

// TypeList의 전체 코드는 https://sourceforge.net/projects/loki-lib/files/Loki/  에서 받을수 있습니다.

struct NullType {};

template <class T, class U>
struct Typelist
{
	typedef T Head;
	typedef U Tail;
};

template
<
	typename T1 = NullType, typename T2 = NullType, typename T3 = NullType,
	typename T4 = NullType, typename T5 = NullType, typename T6 = NullType,
	typename T7 = NullType, typename T8 = NullType, typename T9 = NullType,
	typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
	typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
	typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
>
struct MakeTypelist
{
private:
	typedef typename MakeTypelist
		<
		T2, T3, T4,
		T5, T6, T7,
		T8, T9, T10,
		T11, T12, T13,
		T14, T15, T16,
		T17, T18
		>
		::Result TailResult;

public:
	typedef Typelist<T1, TailResult> Result;
};

template<> struct MakeTypelist<>
{
	typedef NullType Result;
};

// Length

template <class TList> struct Length;
template <> struct Length<NullType>
{
	enum { value = 0 };
};

template <class T, class U>
struct Length< Typelist<T, U> >
{
	enum { value = 1 + Length<U>::value };
};

// TypeAt
template <class TList, unsigned int index> struct TypeAt;

template <class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0>
{
	typedef Head Result;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i>
{
	typedef typename TypeAt<Tail, i - 1>::Result Result;
};

// IndexOf
template <class TList, class T> struct IndexOf;

template <class T>
struct IndexOf<NullType, T>
{
	enum { value = -1 };
};

template <class T, class Tail>
struct IndexOf<Typelist<T, Tail>, T>
{
	enum { value = 0 };
};

template <class Head, class Tail, class T>
struct IndexOf<Typelist<Head, Tail>, T>
{
private:
	enum { temp = IndexOf<Tail, T>::value };
public:
	enum { value = (temp == -1 ? -1 : 1 + temp) };
};

// Append

template <class TList, class T> struct Append;

template <> struct Append<NullType, NullType>
{
	typedef NullType Result;
};

template <class T> struct Append<NullType, T>
{
	typedef Typelist<T, NullType> Result;
};

template <class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail> >
{
	typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T>
{
	typedef Typelist<Head,
		typename Append<Tail, T>::Result>
		Result;
};

// Erase 
template <class TList, class T> struct Erase;

template <class T>                         // Specialization 1
struct Erase<NullType, T>
{
	typedef NullType Result;
};

template <class T, class Tail>             // Specialization 2
struct Erase<Typelist<T, Tail>, T>
{
	typedef Tail Result;
};

template <class Head, class Tail, class T> // Specialization 3
struct Erase<Typelist<Head, Tail>, T>
{
	typedef Typelist<Head,
		typename Erase<Tail, T>::Result>
		Result;
};

// Replace

template <class TList, class T, class U> struct Replace;

template <class T, class U>
struct Replace<NullType, T, U>
{
	typedef NullType Result;
};

template <class T, class Tail, class U>
struct Replace<Typelist<T, Tail>, T, U>
{
	typedef Typelist<U, Tail> Result;
};

template <class Head, class Tail, class T, class U>
struct Replace<Typelist<Head, Tail>, T, U>
{
	typedef Typelist<Head,
		typename Replace<Tail, T, U>::Result>
		Result;
};
int main()
{
	typedef MakeTypelist<int, char, double, short>::Result myType;


	// (1) TypeAt : N번째 타입이 무슨 타입인지 알아내는 템플릿 입니다.
	TypeAt<myType, 1>::Result  n; // n은 char 타입이어야 합니다.


	// (2) IndexOf : 특정 타입이 몇번째 있는지 찾아 내는 템플릿입니다.
	cout << IndexOf<myType, double>::value << endl; // 2가 나와야 합니다.


	// (3) Erase : 특정 타입을 제거한 새로운 TypeList 만들기.   최초 발견된것 하나만 제거
	typedef Erase<myType, char>::Result myType2;

	cout << typeid(myType2).name() << endl; // int, double, short 의 TypeList입니다.


	// (4) Replace : 특정 타입을 다른 타입으로 교체한 TypeList 만들기
	typedef Replace<myType, char, float>::Result myType3;
	cout << typeid(myType3).name() << endl; // int, float, double, short 
}
