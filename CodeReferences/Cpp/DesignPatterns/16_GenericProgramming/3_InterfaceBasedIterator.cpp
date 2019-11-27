// Interface based Interator
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


// 모든 반복자의 인터페이스를 먼저 설계하자.      Java           C#
// 1. 반복자 인터페이스.                       - Iterator      IEnumerator
// 2. 반복의 대상(컬렉션) 인터페이스           - Iterable      IEnumerable

template <typename T> struct IEnumerator
{
    virtual bool move_next() = 0;        // ++
    virtual T&   get_object() = 0;       // *

    virtual ~IEnumerator() {}
};

template <typename T>
class CSListEnumerator : public IEnumerator<T>
{
    node<T>* current;
public:
    CSListEnumerator(node<T>* p = 0) : current(p) {}

    virtual bool move_next()
    {
        current = current->next;
        return current != NULL;
    }

    virtual T& get_object() 
    { 
        return current->data;
    }
};


// 컨테이너에서 반복자 꺼내기
// 1. STL:  begin()/end() => 암시적 약속 (generic 다형성)
// 2. C#,JAVA: 인터페이스 기반 함수 약속
//    Tizen

// 모든 컨테이너는 아래 인터페이스를 구현해야 한다.
template <typename T> struct IEnumerable
{
    virtual IEnumerator<T>* get_enumerator_n() = 0;
    virtual ~IEnumerable() {}
};

// SList class
template <typename T>
class CSList : public IEnumerable<T>
{
public:
    CSList();
    ~CSList();
    virtual IEnumerator<T>* get_enumerator_n()
    {
        return new CSListEnumerator<T>(head);
    }
    // 일반적으로 함수 내에서 new를 해서 리턴해야 한다면, 스마트 포인터를
    // 사용하는 경우가 많다.
    // Tizen: UniquePtr<>

    // free -> strdup(s);
    // char* p = strdup(s);

    // char* s = "hello";
    // char* p = malloc(strlen(s) + 1);
    // strcpy(p, s);

    // node의 Constructor를 잘 활용한 코드입니다.
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

int main()
{
    CSList<int> s;
    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    //cout << s.front() << endl;

    IEnumerator<int>* p = s.get_enumerator_n();

    do {
        cout << p->get_object() << endl;
    } while (p->move_next());

    // 반드시 delete를 수행해야 합니다.
    delete p;

    system("pause");
    return 0;
}