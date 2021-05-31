#include <iostream>

using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;

	Node(const T& a, Node* n) : data(a), next(n) {}
};

template<typename T>
class Slist
{
private:
	Node<T>* head = nullptr;
public:
	explicit Slist(void){}
	virtual ~Slist(){}
	void push_front(const T& a)
	{
		head = new Node<T>(a, head);
	}
};


int main()
{
	Slist<int> s;

	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);

	return 0;
}