#include <iostream>
using namespace std;

template<typename T, typename U> struct Object
{
	static void foo() { cout << "T, U" << endl; }
};
template<typename T, typename U> struct Object<T*, U*>
{
	static void foo() { cout << "T*, U*" << endl; }
};

template<typename T, typename U> struct Object<T*, U>
{
	static void foo() { cout << "T*, U" << endl; }
};

// 핵심 : primary template 인자가 2개일때
// 1. 사용자는 반드시 2개를 사용해야 한다. Object<int, int>

// 2. 부분 특수화 모양(오른쪽끝)도 2개 있어야 한다.  => Object<T, T>

// 3. 부분 특수화 버전의 인자 갯수는 달라질수 있다.

template<typename T> struct Object<T, T>
{
	static void foo() { cout << "T, T" << endl; }
};

template<typename U> struct Object<double, U>
{
	static void foo() { cout << "double, U" << endl; }
};

template<typename T, typename U, typename V> struct Object< T, Object<U, V> > 
{
	static void foo() { cout << "T, Object<U, V>" << endl; }
};

int main()
{
	Object<int, double>::foo();	 // T,  U
	Object<int*, double*>::foo();// T*, U*
	Object<int*, double>::foo(); // T*, U
	Object<int, int>::foo();     // T, T 
	Object<double, char>::foo(); // double, U
	Object<short, Object<short, char>>::foo(); // T, Object<U, V> 
	
}
