// 2_참조계수 - 매우 중요합니다.

// Reference Counter?

#include <iostream>
using namespace std;

// 객체의 수명을 참조 계수로 관리하는 경우가 많습니다.
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

// RefCountedObject*를 바로 사용하면 참조 계수를 매번 관리해야 한다.
// 불편하므로 참조 계수를 자동으로 관리해주는 클래스를 만들자.

template <typename T>
class Ptr
{
public:
    Ptr(T* p)
        : ptr(p)
    {
        ptr->add_ref();         // 규칙 1.
    }
    Ptr(const Ptr& p)
        : ptr(p.ptr)
    {
        ptr->add_ref();         // 규칙 2.
    }

    ~Ptr()
    {
        ptr->release();         // 규칙 3.
    }

    // 진짜 포인터 처럼 보여야 한다.
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


// 기존의 객체를 참조 계수 기반으로 관리하고 싶다.
// shared_ptr<>
// shared_ptr<Image> p(new Image)
// shared_ptr<Image> p = make_shared<Image>();  // 연속된 메모리로 만들어 준다.

// Smart Pointer - Resource의 소유권
// - shared_ptr : 참조 계수 (Ref Couter) 기반, 느려질 수 있음. Atomic procedure 수행을 위해 Clock을 잠시 멈춤
// - unique_ptr : 복사 금지, 소유권 이전은 가능
//          Effective Modern C++ - 인사이트, 류광
//              unique_ptr<int> p1(new int);
//              unique_ptr<int> p2 = p1;            // 에러, 복사금지
//              unique_ptr<int> p2 = std::move(p1); // 소유권 이전, p1 -> 0


// http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/ 참고

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
