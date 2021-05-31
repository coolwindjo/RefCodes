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

#if 0
	typedef Slist_iterator<T> iterator;
#else
	using iterator = Slist_iterator<T>;
#endif

	iterator begin()
	{
		return iterator(head);
	}

	iterator end()
	{
		return iterator(nullptr);
	}
};

template<typename T1, typename T2>
T1 efind(T1 first, T1 last, const T2 value)
{
	while (first != last) {
		if (value == *first) {
			break;
		}
		++first;
		// first++;
	}
	return first;
}

int main()
{
	Slist<int> s;

	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);

	Slist<int>::iterator p = s.begin();

	/*/
	Slist<int>::iterator p2 = efind(s.begin(), s.end(), 20);	// 20
	/*/
	Slist<int>::iterator p2 = efind(s.begin(), s.end(), 120);	// failed!
	//*/

	if (p2 == s.end()) {
		cout << "failed" <<endl;
	}
	else {
		cout << *p2 <<endl;	//20
	}

	return 0;
}