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

// CSList의 Iterator를 설계해봅시다.
// - Container 구간을 표현하는 타입(Smart Pointer)

template <typename T>
class CSListIterator
{
public:
    CSListIterator(node<T>* p = 0);
    ~CSListIterator();
    // ==, != 를 제공한다.
    inline bool operator==(const CSListIterator& t) 
    { 
        return t.current == current; 
    }
    inline bool operator!=(const CSListIterator& t)
    {
        return t.current != current; 
    }

    // 값을 얻는 연산
    inline T& operator*()
    { 
        return current->data; 
    }

    // 이동하는 연산
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
    // 모든 컨테이너 설계자는 자신의 반복자 이름을 미리 약속된 형태로
    // 외부에 알려야 한다.
    typedef CSListIterator<T> iterator;

    // 모든 컨테이너의 설계자는 자신의 처음과 끝 다음을 가르키는 반복자를
    // 꺼낼 수 있는 연산을 제공해야 한다.
    // begin() / end()
    // 반복자를 꺼내는 함수 
    CSListIterator<T> begin() { return CSListIterator<T>(head); }
    CSListIterator<T> end() { return CSListIterator<T>(NULL); }

    void push_front(const T& a)
    {
        // node의 Constructor
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