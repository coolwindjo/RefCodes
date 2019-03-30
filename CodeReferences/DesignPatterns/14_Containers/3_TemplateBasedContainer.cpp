#include <iostream>
#include <vector>
using namespace std;

// ��� 2. Template based Container
//  - Java, C#, Object-C: Generic

// ����: Type �������� �پ�� ǥ�� Type�Ӹ��ƴ϶�, Object�� ���� ���� �ϴ�.
//      ���� �� ĳ������ �ʿ� ����.

// ����: Template�̹Ƿ� �������� Type�� ����ϸ� List�� ���� �ڵ尡 ��������.
//      �ڵ� �޸� Overhead�� �ִ�.


// ���ڸ� ����             ǥ�� Ÿ��                 ��ü Ÿ��
// call by value           void foo(int n)          void foo(const AAA& n)
// call by reference       void foo(int& n)         void foo(AAA& n)

//                          T - ǥ�� Ÿ�� �Ǵ� ��ü Ÿ�Ե� �� �� �ִ�.
//                          void foo(const T&)


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

template <typename T>
class CSList
{
public:
    CSList();
    ~CSList();
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
    cout << s.front() << endl;

    system("pause");
    return 0;
}