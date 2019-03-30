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


int main()
{
    Image* p1 = new Image;      // ��Ģ 1. ��ü�� ����� ���� ��� ����
    p1->add_ref();

    Image* p2 = p1;             // ��Ģ 2. Pointer�� �����ϸ� ���� ��� ����
    p2->add_ref();

    p1->release();              // ��Ģ 3. Object Pointer ��� �� ���� ��� ����
    p2->release();

    system("pause");
    return 0;
}