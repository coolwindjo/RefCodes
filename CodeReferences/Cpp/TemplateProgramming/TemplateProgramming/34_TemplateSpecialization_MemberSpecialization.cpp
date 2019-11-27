#include <iostream>

using namespace std;

/// Primary template
template<typename T>
class Stack {
public:
	void push(T a);
	void pop() { cout << "T pop!" << endl; }
};

template<typename T>
void Stack<T>::push(T a) { cout << "T" << endl; }

/// 특정 member function 만 Partial specialization
//template<typename T>
//void Stack<T*>::push(T a) { cout << "T*" << endl; }

/// 특정 member function 만 Specialization
template<>
void Stack<char*>::push(char* a) { cout << "char*" << endl; }

int main()
{
	Stack<int> s1; s1.push(0); s1.pop();
	Stack<int*> s2; s2.push(0); s2.pop();
	Stack<char*> s3; s3.push(0); s3.pop();

	system("pause");
	return 0;
}