#include <iostream>
#include <vector>
using namespace std;

// 방법 2. Template based Container
//  - Java, C#, Object-C: Generic

// 장점: Type 안정성이 뛰어나고 표준 Type뿐만아니라, Object도 저장 가능 하다.
//      꺼낼 때 캐스팅이 필요 없다.

// 단점: Template이므로 여러가지 Type에 사용하면 List의 기계어 코드가 많아진다.
//      코드 메모리 Overhead가 있다.


// 인자를 전달             표준 타입                 객체 타입
// call by value           void foo(int n)          void foo(const AAA& n)
// call by reference       void foo(int& n)         void foo(AAA& n)

//                          T - 표준 타입 또는 객체 타입도 될 수 있다.
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
    cout << s.front() << endl;

    system("pause");
    return 0;
}