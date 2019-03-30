#include <iostream>
using namespace std;

// ��� 3. Thin Template
//  : Mobile ȯ�濡�� ���� ����

// CSListImpl�� ���� ����ϸ� ĳ���� ������ �����ϴ�.
// ����ڰ� ���ϰ� ����� �� �ֵ��� ������ ���� �޴� �ڽ� Ŭ������ 
// ���ø����� ��������.

struct node
{
    void* data;
    node* next;
    node(void* a, node* n)
        : data(a)
        , next(n)
    {}
};

class CSListImpl
{
public:
    CSListImpl();
    ~CSListImpl();

    // node�� Constructor�� �� Ȱ���� �ڵ��Դϴ�.
    void push_front(void* a)
    {
        // node�� Constructor
        head = new node(a, head);
    }
    void* front()
    {
        return head->data;
    }
private:
    node* head;
};

CSListImpl::CSListImpl()
    : head(0)
{
}

CSListImpl::~CSListImpl()
{
}


template <typename T>
//class CSList : public CSListImpl
class CSList : private CSListImpl   // CSListImpl�� �����.
{
public:
    CSList();
    ~CSList();
    //void push_front(const T& a)   
    inline void push_front(const T& a)  // inline���� code memory ���ϸ� ����
    {
        // const T& -> const T*
        CSListImpl::push_front(const_cast<T*>(&a));
    }
    //const T& front()
    inline const T& front()
    {
        return *static_cast<T*>(CSListImpl::front());
    }
private:

};

template <typename T>
CSList<T>::CSList()
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
    cout << s.front() << endl;

    system("pause");
    return 0;
}