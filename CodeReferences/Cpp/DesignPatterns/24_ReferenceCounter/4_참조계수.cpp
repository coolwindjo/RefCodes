// 2_참조계수 - 매우 중요합니다.

// Reference Counter?

#include <iostream>
using namespace std;

// 객체의 수명을 참조 계수로 관리하는 경우가 많습니다.
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
    Image* p1 = new Image;      // 규칙 1. 객체를 만들면 참조 계수 증가
    p1->add_ref();

    Image* p2 = p1;             // 규칙 2. Pointer를 복사하면 참조 계수 증가
    p2->add_ref();

    p1->release();              // 규칙 3. Object Pointer 사용 후 참조 계수 감소
    p2->release();

    system("pause");
    return 0;
}