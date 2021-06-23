#include <iostream>
using namespace std;
// primary template
template<typename T> class Stack
{
public: void push(T v) { cout << "T" << endl; }
};
// partial specialization( �κ� Ư��ȭ )
template<typename T> class Stack<T*>
{
public:	void push(T* v) { cout << "T*" << endl; }
};
// specialization( Ư��ȭ )
template<> class Stack<char*>
{
public:	void push(char* v) { cout << "char*" << endl; }
};

int main()
{
	Stack<int>   s1; s1.push(0);
	Stack<int*>  s2; s2.push(0);
	Stack<char*> s3; s3.push(0);
}