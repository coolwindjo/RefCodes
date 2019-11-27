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
// ����: ������ Object�� �ٸ� Object�� Pointer�� ������ �����ϴ� ��
// ��������: "->"�� "*" �����ڸ� Overloading�ؼ� ������ó�� ���̰� �����.
// ����: ��¥ �����Ͱ� �ƴ϶� ��ü�̴�.
//          ����/����/����/�Ҹ��� ��� ������ ������ �� �ִ�.
// Ȱ��: ��ǥ�� Ȱ���� �Ҹ��ڿ����� �ڵ� ���� ����̴�.

// C++ ǥ�ؿ����� �̹� �پ��� ��å�� ������ �ִ� ����Ʈ �����͸� �����ϰ� �ֽ��ϴ�.
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