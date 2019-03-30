#include <iostream>

using namespace std;

/// Primary template
template<typename T>
class Stack { public:	
	void push(T a) { cout << "T" << endl; }
	void pop() { cout << "T pop!" << endl; }
};
/// Partial specialization
template<typename T>
class Stack<T*>: public Stack<T> { public:	void push(T a) { cout << "T*" << endl; } };
/// Specialization
template<>
class Stack<char*> { public:	void push(char* a) { cout << "char*" << endl; } };

int main()
{
	Stack<int> s1; s1.push(0); s1.pop();
	Stack<int*> s2; s2.push(0); s2.pop();
	Stack<char*> s3; s3.push(0);

	system("pause");
	return 0;
}