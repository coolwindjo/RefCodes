// Smart Pointer
#include <iostream>
using namespace std;

class Car
{
public:
    Car() { cout << "Resource allocation" << endl; }
    ~Car() { cout << "Resource free" << endl; }

    void go() { cout << "A car goes." << endl; }
};

// Smart Pointer
// 개념: 임의의 Object가 다른 Object의 Pointer의 역할을 수행하는 것
// 구현원리: "->"와 "*" 연산자를 Overloading해서 포인터처럼 보이게 만든다.
// 장점: 진짜 포인터가 아니라 객체이다.
//          생성/복사/대입/소멸의 모든 과정을 제어할 수 있다.
// 활용: 대표적 활용은 소멸자에서의 자동 삭제 기능이다.

// C++ 표준에서도 이미 다양한 정책을 가지고 있는 스마트 포인터를 제공하고 있습니다.
//  C++98/03 - auto_ptr
//  C++11/14 - unique_ptr, shared_ptr, weak_ptr, auto_ptr(deprecated)

template <typename T>
class CSmtPtr
{
public:
    //CSmtPtr(T* p = 0);
    //~CSmtPtr();
    inline CSmtPtr(T* p = 0);
    inline ~CSmtPtr();

    //T* operator->()
    inline T* operator->()
    {
        return object;
    }
    //T& operator*()
    inline T& operator*()
    {
        return *object;
    }
private:
    T* object;
};

template <typename T>
CSmtPtr<T>::CSmtPtr(T* p)
    : object(p)
{
}

template <typename T>
CSmtPtr<T>::~CSmtPtr()
{
    delete object;
}


int main()
{
    CSmtPtr<Car> s_ptr = new Car;
    s_ptr->go();
    (*s_ptr).go();

    //delete s_ptr;

    system("pause");
    return 0;
}