#include <iostream>
using namespace std;

#include <memory>

// 순환 참조
//  => 강한 참조의 개념과 약한 참조의 개념을 이해하고 구현할 수 있어야 한다.
//  => 소유권

// Node p = new Node(); -> 강한 참조
// WeakReference<Node> wp = new WeakReference<>(new Node());
// SoftReference<Node>
//  => 약한 참조

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
