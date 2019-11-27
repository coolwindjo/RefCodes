#include <iostream>
using namespace std;

struct node
{
    int data;
    node* next;
    node(int a, node* n)
        : data(a)
        , next(n)
    {}
};

class CSList
{
public:
    CSList();
    ~CSList();
    // node의 Constructor를 잘 활용한 코드입니다.
    void push_front(int a)
    {
        // node의 Constructor
        head = new node(a, head);
    }
    int front()
    {
        return head->data;
    }
private:
    node* head;
};

CSList::CSList()
    : head(0)
{
}

CSList::~CSList()
{
}

int main()
{
    CSList s;
    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    cout << s.front() << endl;

    system("pause");
    return 0;
}