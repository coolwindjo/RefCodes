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

// �ٽ� : primary template ���ڰ� 2���϶�
// 1. ����ڴ� �ݵ�� 2���� ����ؾ� �Ѵ�. Object<int, int>

// 2. �κ� Ư��ȭ ���(�����ʳ�)�� 2�� �־�� �Ѵ�.  => Object<T, T>

// 3. �κ� Ư��ȭ ������ ���� ������ �޶����� �ִ�.

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
