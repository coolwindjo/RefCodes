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


// ��� �ݺ����� �������̽��� ���� ��������.      Java           C#
// 1. �ݺ��� �������̽�.                       - Iterator      IEnumerator
// 2. �ݺ��� ���(�÷���) �������̽�           - Iterable      IEnumerable

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


// �����̳ʿ��� �ݺ��� ������
// 1. STL:  begin()/end() => �Ͻ��� ��� (generic ������)
// 2. C#,JAVA: �������̽� ��� �Լ� ���
//    Tizen

// ��� �����̳ʴ� �Ʒ� �������̽��� �����ؾ� �Ѵ�.
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
    // �Ϲ������� �Լ� ������ new�� �ؼ� �����ؾ� �Ѵٸ�, ����Ʈ �����͸�
    // ����ϴ� ��찡 ����.
    // Tizen: UniquePtr<>

    // free -> strdup(s);
    // char* p = strdup(s);

    // char* s = "hello";
    // char* p = malloc(strlen(s) + 1);
    // strcpy(p, s);

    // node�� Constructor�� �� Ȱ���� �ڵ��Դϴ�.
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

    // �ݵ�� delete�� �����ؾ� �մϴ�.
    delete p;

    system("pause");
    return 0;
}