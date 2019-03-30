#include <iostream>

using namespace std;

/// Partial specialization �� default parameter
/// Primary template
template<typename T, int N = 10>
class Stack { public:T buff[N]; };

/// Partial specialization: Default ���� ǥ������ �ʴ´�.
template<typename T, int N>
class Stack<T*, N> { public:T buff[N]; };

int main()
{
	Stack<int> s1; // N == 10
	Stack<int*> s2; // N == 10

	system("pause");
	return 0;
}