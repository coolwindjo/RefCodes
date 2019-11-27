// 2_������� - �ſ� �߿��մϴ�.

// Reference Counter?

#include <iostream>
using namespace std;

// ��ü�� ������ ���� ����� �����ϴ� ��찡 �����ϴ�.
class Image
{
    int mCount;
public:
    Image() : mCount(0) {}
    ~Image() { cout << "Image destructed" << endl; }

    void add_ref() { ++mCount; }
    void release()
    {
        if (--mCount == 0)
            delete this;
    }
};

// Image*�� �ٷ� ����ϸ� ���� ����� �Ź� �����ؾ� �Ѵ�.
// �����ϹǷ� ���� ����� �ڵ����� �������ִ� Ŭ������ ������.
class ImageProxy
{
public:
    ImageProxy(Image* p)
        : ptr(p)
    {
        ptr->add_ref();         // ��Ģ 1.
    }
    ImageProxy(const ImageProxy& p)
        : ptr(p.ptr)
    {
        ptr->add_ref();         // ��Ģ 2.
    }

    ~ImageProxy()
    {
        ptr->release();         // ��Ģ 3.
    }

private:
    Image* ptr;
};


int main()
{
    if (true)
    {
        ImageProxy p1 = new Image;
        ImageProxy p2 = p1;
        //ImageProxy p3 = new Image;
    }

    system("pause");
    return 0;
}

//int main()
//{
//    Image* p1 = new Image;      // ��Ģ 1. ��ü�� ����� ���� ��� ����
//    p1->add_ref();
//
//    Image* p2 = p1;             // ��Ģ 2. Pointer�� �����ϸ� ���� ��� ����
//    p2->add_ref();
//
//    p1->release();              // ��Ģ 3. Object Pointer ��� �� ���� ��� ����
//    p2->release();
//
//    system("pause");
//    return 0;
//}