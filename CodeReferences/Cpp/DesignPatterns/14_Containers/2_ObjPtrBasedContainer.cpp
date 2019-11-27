#include <iostream>
using namespace std;

// ��� 1. object* ����� Container
// java, C#: Object
// Object-C: NSObject
// MFC: CObject
// Qt: QObject


// ����:
// 1. Ÿ�� �������� ��������. �Ǽ��� �ٸ� Ÿ���� �־ ������ �ð��� ������
//    �߻����� �ʴ´�.

// 2. ���� ���� �� �׻� �ش� Ÿ������ ĳ�����ؾ� �Ѵ�.
// 3. ��ü�� �ƴ� ǥ�� Ÿ��(primitive type)�� ������ �� ����.
//    wrapper class�� �ʿ��ϴ�. - ǥ�� Ÿ���� ���۷��� Ÿ��
//    int - Integer
//    double - Double

// ����:
//  template �� ����ϰ� �Ǹ�, �ڵ� �޸� ���� ��尡 �ִ�.


// Ancestor Object.
class AObject
{
public:
    AObject();
    ~AObject();

private:

};

AObject::AObject()
{
}

AObject::~AObject()
{
}

// Library�� ��� class���� AObject�� �ڽ��̾�� �Ѵ�.
class Dialog : public AObject {};
class Point : public AObject {};
class Rect : public AObject {};

class Integer : public AObject
{
    int value;
public:
    Integer(int v) : value(v) {}
    int getValue() { return value; }
};

// SList
struct node
{
    AObject* data;
    node* next;
    node(AObject* a, node* n)
        : data(a)
        , next(n)
    {}
};

class CSList
{
public:
    CSList();
    ~CSList();
    // node�� Constructor�� �� Ȱ���� �ڵ��Դϴ�.
    void push_front(AObject* a)
    {
        // node�� Constructor
        head = new node(a, head);
    }
    AObject* front()
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
    s.push_front(new Point);
    s.push_front(new Point);
    s.push_front(new Point);

    // s.push_front(3); // ?
    s.push_front(new Integer(3));  // auto-boxing

    // s.push_front(new Dialog);  // ??? �Ǽ�!!!!

    // int n = s.front(); - auto unboxing
    int n = static_cast<Integer*>(s.front())->getValue();   // Intended unboxing
    cout << n << endl;

    system("pause");
    return 0;
}