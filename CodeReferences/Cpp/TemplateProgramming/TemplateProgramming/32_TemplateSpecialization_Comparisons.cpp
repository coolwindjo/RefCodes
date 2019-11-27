#include <iostream>

using namespace std;

template<typename T, typename U>
class Test { public:	void foo() { cout << "T, U" << endl; } };
template<typename T, typename U>
class Test<T*, U> { public:	void foo() { cout << "T*, U" << endl; } };
template<typename T, typename U>
class Test<T*, U*> { public:	void foo() { cout << "T*, U*" << endl; } };

/// Partly specialization 에는 Template argument 의 갯수를 변경 가능
template<typename T>
class Test<T, T> { public:	void foo() { cout << "T, T" << endl; } };

template<typename T>
class Test<T, char> { public:	void foo() { cout << "T, char" << endl; } };

/// Template Specialization.
template<>
class Test<int, short> { public:	void foo() { cout << "int, short" << endl; } };

template<typename T>
class Test<T*, T*> { public:	void foo() { cout << "T*, T*" << endl; } };

int main()
{
	Test<int, double> t1; t1.foo();
	Test<int*, double> t2; t2.foo();
	Test<int*, double*> t3; t3.foo();
	Test<int, int> t4; t4.foo();
	Test<int, char> t5; t5.foo();
	Test<int, short> t6; t6.foo();

	Test<int*, int*> t7; t7.foo();

	system("pause");
	return 0;
}