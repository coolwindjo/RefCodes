// 2_������� - �ſ� �߿��մϴ�.

// Reference Counter?

#include <iostream>
using namespace std;

// ��ü�� ������ ���� ����� �����ϴ� ��찡 �����ϴ�.
class RefCountedObject
{
    int mCount;
public:
    RefCountedObject() : mCount(0) {}
    ~RefCountedObject() { cout << "Object destructed" << endl; }

    void add_ref() { ++mCount; }
    void release()
    {
        if (--mCount == 0)
            delete this;
    }
};

// RefCountedObject*�� �ٷ� ����ϸ� ���� ����� �Ź� �����ؾ� �Ѵ�.
// �����ϹǷ� ���� ����� �ڵ����� �������ִ� Ŭ������ ������.

template <typename T>
class Ptr
{
public:
    Ptr(T* p)
        : ptr(p)
    {
        ptr->add_ref();         // ��Ģ 1.
    }
    Ptr(const Ptr& p)
        : ptr(p.ptr)
    {
        ptr->add_ref();         // ��Ģ 2.
    }

    ~Ptr()
    {
        ptr->release();         // ��Ģ 3.
    }

    // ��¥ ������ ó�� ������ �Ѵ�.
    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }
private:
    T* ptr;
};


class Image : public RefCountedObject
{
public:
    Image() {}
    ~Image() {}

    void draw() { cout << "Image draw" << endl; }

private:

};


// ������ ��ü�� ���� ��� ������� �����ϰ� �ʹ�.
// shared_ptr<>
// shared_ptr<Image> p(new Image)
// shared_ptr<Image> p = make_shared<Image>();  // ���ӵ� �޸𸮷� ����� �ش�.

// Smart Pointer - Resource�� ������
// - shared_ptr : ���� ��� (Ref Couter) ���, ������ �� ����. Atomic procedure ������ ���� Clock�� ��� ����
// - unique_ptr : ���� ����, ������ ������ ����
//          Effective Modern C++ - �λ���Ʈ, ����
//              unique_ptr<int> p1(new int);
//              unique_ptr<int> p2 = p1;            // ����, �������
//              unique_ptr<int> p2 = std::move(p1); // ������ ����, p1 -> 0


// http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/ ����

int main()
{
    if (true)
    {
        Ptr<Image> p1 = new Image;
        Ptr<Image> p2 = p1;
        Ptr<Image> p3 = new Image;

        p1->draw();
        p2->draw();
        p3->draw();

    }

    system("pause");
    return 0;
}
