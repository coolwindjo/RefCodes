#include <iostream>
#include <iterator>		// for forward_iterator_tag

using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;

	Node(const T& a, Node* n) : data(a), next(n) {}
};

#if 0
template<typename Category,
		 typename T,
		 typename Distance = std::ptrdiff_t,
		 typename Pointer = T*,
		 typename Reference = T&>
struct iterator
{
	using iterator_category = Category;
	using value_type = T;
	using pointer = Pointer;				// stream_iterator나 insert_iterator 에서는 사용하지 않기도 함
	using reference = Reference;
	using difference_type = Reference;		// unsigned int
};
#endif

template<typename T>
class Slist_Iter 
	: public iterator<forward_iterator_tag, T>	// deperecated @ C++17 : 매번 다 쓰지도 않는데 모두 정의를 할 필요가 없다.
{
private:
	Node<T>* current = nullptr;
public:
	explicit Slist_Iter(Node<T>* p = nullptr): current(p) {}
	virtual ~Slist_Iter(){}

	Slist_Iter& operator++()
	{
		current = current->next;
		return *this;
	}

	T& operator*()
	{
		return current->data;
	}

	bool operator==(const Slist_Iter& it)
	{
		return current == it.current;
	}

	bool operator!=(const Slist_Iter& it)
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
	typedef Slist_Iter<T> iterator;
#else
	using iterator = Slist_Iter<T>;
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