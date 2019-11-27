// 2 iterator
#include <iostream>
#include <vector>
using namespace std;

// Template based Container

template <typename T>
struct node
{
    T data;
    node* next;
    node(const T& a, node* n)
        : data(a)
        , next(n)
    {}
};

// CSList�� Iterator�� �����غ��ô�.
// - Container ������ ǥ���ϴ� Ÿ��(Smart Pointer)

template <typename T>
class CSListIterator
{
public:
    CSListIterator(node<T>* p = 0);
    ~CSListIterator();
    // ==, != �� �����Ѵ�.
    inline bool operator==(const CSListIterator& t) 
    { 
        return t.current == current; 
    }
    inline bool operator!=(const CSListIterator& t)
    {
        return t.current != current; 
    }

    // ���� ��� ����
    inline T& operator*()
    { 
        return current->data; 
    }

    // �̵��ϴ� ����
    //inline void operator++()
    inline CSListIterator& operator++()
    {
        current = current->next;
        //return current->next;
        return *this;
    }

private:
    node<T>* current;
};

template <typename T>
CSListIterator<T>::CSListIterator(node<T>* p)
    : current(p)
{
}

template <typename T>
CSListIterator<T>::~CSListIterator()
{
}


// SList class
template <typename T>
class CSList
{
public:
    CSList();
    ~CSList();
    // ��� �����̳� �����ڴ� �ڽ��� �ݺ��� �̸��� �̸� ��ӵ� ���·�
    // �ܺο� �˷��� �Ѵ�.
    typedef CSListIterator<T> iterator;

    // ��� �����̳��� �����ڴ� �ڽ��� ó���� �� ������ ����Ű�� �ݺ��ڸ�
    // ���� �� �ִ� ������ �����ؾ� �Ѵ�.
    // begin() / end()
    // �ݺ��ڸ� ������ �Լ� 
    CSListIterator<T> begin() { return CSListIterator<T>(head); }
    CSListIterator<T> end() { return CSListIterator<T>(NULL); }

    void push_front(const T& a)
    {
        // node�� Constructor
        head = new node<T>(a, head);
    }
    const T& front()
    {
        return head->data;
    }

private:
    node<T>* head;
};

template <typename T>
CSList<T>::CSList()
    : head(0)
{
}

template <typename T>
CSList<T>::~CSList()
{
}


template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
    while (first != last && *first != value)
        ++first;

    return first;
}

int main()
{
    CSList<int> s;
    s.push_front(10);
    s.push_front(20);
    s.push_front(30);

    //cout << s.front() << endl;

    // CSListIterator<int> p = xfind(s.begin(), s.end(), 20);

    CSList<int>::iterator p = xfind(s.begin(), s.end(), 20);
    if (p != s.end())
        cout << *p << endl;
    
    system("pause");
    return 0;
}