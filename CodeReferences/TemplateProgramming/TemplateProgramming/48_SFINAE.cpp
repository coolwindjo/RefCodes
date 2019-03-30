#include <iostream>

using namespace std;

/// SFINAE : Substituition Failure Is No An Error.

//void foo(int n) { cout << "int" << endl; }
void foo(...) { cout << "..." << endl; }

template<typename T>
//void foo(T n) { cout << "T" << endl; }
//int foo(T n) { cout << "T" << endl; return 0; }
typename T::type foo(T n) { cout << "T" << endl; return 0; }	///< 아예 후보에서 제외됨

int main()
{
	foo(1);

	system("pause");
	return 0;
}