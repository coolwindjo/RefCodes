#include <iostream>
using namespace std;

// 방법 1. object* 기반의 Container
// java, C#: Object
// Object-C: NSObject
// MFC: CObject
// Qt: QObject


// 단점:
// 1. 타입 안정성이 떨어진다. 실수로 다른 타입을 넣어도 컴파일 시간에 에러가
//    발생하지 않는다.

// 2. 값을 꺼낼 때 항상 해당 타입으로 캐스팅해야 한다.
// 3. 객체가 아닌 표준 타입(primitive type)은 저장할 수 없다.
//    wrapper class가 필요하다. - 표준 타입의 레퍼런스 타입
//    int - Integer
//    double - Double

// 장점:
//  template 을 사용하게 되면, 코드 메모리 오버 헤드가 있다.


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

// Library의 모든 class들은 AObject의 자식이어야 한다.
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
    // node의 Constructor를 잘 활용한 코드입니다.
    void push_front(AObject* a)
    {
        // node의 Constructor
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

    // s.push_front(new Dialog);  // ??? 실수!!!!

    // int n = s.front(); - auto unboxing
    int n = static_cast<Integer*>(s.front())->getValue();   // Intended unboxing
    cout << n << endl;

    system("pause");
    return 0;
}