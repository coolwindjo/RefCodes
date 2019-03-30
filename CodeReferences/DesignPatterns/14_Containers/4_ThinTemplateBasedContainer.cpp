#include <iostream>
using namespace std;

// 방법 3. Thin Template
//  : Mobile 환경에서 많이 사용됨

// CSListImpl을 직접 사용하면 캐스팅 때문에 불편하다.
// 사용자가 편리하게 사용할 수 있도록 구현을 물려 받는 자식 클래스를 
// 템플릿으로 제공하자.

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

    // node의 Constructor를 잘 활용한 코드입니다.
    void push_front(void* a)
    {
        // node의 Constructor
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
class CSList : private CSListImpl   // CSListImpl을 감춘다.
{
public:
    CSList();
    ~CSList();
    //void push_front(const T& a)   
    inline void push_front(const T& a)  // inline으로 code memory 부하를 줄임
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