#include <iostream>

using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;

	Node(const T& a, Node* n) : data(a), next(n) {}
};

template<typename T>
class Slist_iterator
{
private:
	Node<T>* current = nullptr;
public:
	explicit Slist_iterator(Node<T>* p = nullptr): current(p) {}
	virtual ~Slist_iterator(){}

	Slist_iterator& operator++()
	{
		current = current->next;
		return *this;
	}

	T& operator*()
	{
		return current->data;
	}

	bool operator==(const Slist_iterator& it)
	{
		return current == it.current;
	}

	bool operator!=(const Slist_iterator& it)
	{
		return current != it.current;
	}

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

	Slist_iterator<T> begin()
	{
		return Slist_iterator<T>(head);
	}

	Slist_iterator<T> end()
	{
		return Slist_iterator<T>(nullptr);
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

	Slist_iterator<int> p = s.begin();

	cout << *p <<endl; //50
	++p;
	cout << *p <<endl; //40

	while (p != s.end()) {
		cout << *p <<endl;
		++p;
	}

	return 0;
}