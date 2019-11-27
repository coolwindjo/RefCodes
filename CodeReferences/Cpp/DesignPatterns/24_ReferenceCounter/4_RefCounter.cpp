#include <iostream>
using namespace std;

#include <memory>

// ��ȯ ����
//  => ���� ������ ����� ���� ������ ������ �����ϰ� ������ �� �־�� �Ѵ�.
//  => ������

// Node p = new Node(); -> ���� ����
// WeakReference<Node> wp = new WeakReference<>(new Node());
// SoftReference<Node>
//  => ���� ����

struct Node
{
    ~Node() { cout << "node destructed" << endl; }
    /*
    shared_ptr<node> next;
    /*/
    weak_ptr<Node> next;
    //*/
};


int main()
{
    if (true)
    {
        shared_ptr<Node> p1(new Node);
        shared_ptr<Node> p2(new Node);

        p1->next = p2;
        p2->next = p1;      // Circular referencing

        shared_ptr<Node> p = p1->next.lock();

    }

    system("pause");
    return 0;
}
