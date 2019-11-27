#include <iostream>
using namespace std;

// list is already present.
#include <list>

// but, client require a stack.
// 2. reuse the list to make a stack.

// Adapter pattern : ���� Ŭ������ �������̽�(�Լ� �̸�)�� �����ؼ�
//                  ����ڰ� �䱸�ϴ� ���ο� Ŭ���� ó�� ���̰� �ϴ� ����

// Library�� ���� ����� �� �ֵ��� ������ �ϰ�,
// �߸� ����ϱ� ��ư� ������ �Ѵ�.

// private inherence : �θ� Ŭ�����κ��� ������ ���� ������, (�ڽ��� ���������� ���������)
//                      �������̽��� ���� ���� �ʰڴ�. (�θ��Լ��� �ܺη� �������� �ʰڴ�.)

template <typename T>
//class stack : public list<T>
class stack : private list<T>
{
public:
    using list<T>::push_back;

    void push(const T& a)
    {
        push_back(a);
    }
    void pop()
    {
        pop_back();
    }
    T& top()
    {
        return back();
    }
};

int main()
{
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);


    system("pause");
    return 0;
}