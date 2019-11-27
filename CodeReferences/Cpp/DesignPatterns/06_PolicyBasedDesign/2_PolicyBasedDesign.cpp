#include <iostream>
using namespace std;

// Effective Java

// API Design on C++

// C++ - ��ı ���̾
// Effective C++

// More Effective C++
// Modern Effective C++
// Effective STL

// ��� ����
// Exceptional C++
// More Exceptional C++
// Exceptional C++ Style

// ��� ���� & �ȵ巹�� �˷���帣��
// C++ Coding Style

// Modern C++ Design


// �������� (Policy-based) Design   "Modern C++ Design = Andre Alexandrocu - compile�� �ȵǴ� template �ڵ带 ���� ���(õ��)"
// => ��å�� ���� �ڵ带 Compile time�� ������ ���� ��� => ������ ����ȭ�� �����ϴ�.
// => C++ ǥ�� Library�� �ٽ� ������ ���

// ����: �����Լ��� �ƴ� inline �Լ��̴�. ȣ�⿡ ���� ���� ���ϰ� ����.
// ����: ��å Class�� Function�� �ƴ� template ���ڷ� ���޵ǹǷ�,
//      Runtime�� ��å�� ��ü�ϴ� ���� �Ұ����ϴ�.
//      => ������ �� ��, ��å�� �����ȴ�!!

class SingleThread
{
public:
    //void lock() {}
    //void unlock() {}
    inline void lock() {}
    inline void unlock() {}
};

class MultiThread
{
public:
    void lock()
    {
        cout << "Mutex lock" << endl;
    }
    void unlock()
    {
        cout << "Mutex unlock" << endl;
    }
};

// Inherence�� ����� Policy-based Design
template <typename T, typename ThreadModel = SingleThread>
class List : public ThreadModel
{
public:
    void push_front(const T& a)
    {
        lock();
        //....
        unlock();
    }
};

List <int, MultiThread> st;

int main()
{
    st.push_front(10);

    system("pause");
    return 0;
}