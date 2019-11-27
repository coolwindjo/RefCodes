#include <iostream>
using namespace std;

// Effective Java

// API Design on C++

// C++ - 스캇 마이어스
// Effective C++

// More Effective C++
// Modern Effective C++
// Effective STL

// 허브 셔터
// Exceptional C++
// More Exceptional C++
// Exceptional C++ Style

// 허브 셔터 & 안드레이 알렉산드르쿠
// C++ Coding Style

// Modern C++ Design


// 단위전략 (Policy-based) Design   "Modern C++ Design = Andre Alexandrocu - compile은 안되는 template 코드를 만든 사람(천재)"
// => 정책을 담은 코드를 Compile time에 생성해 내는 기술 => 성능의 최적화가 가능하다.
// => C++ 표준 Library의 핵심 디자인 기법

// 장점: 가상함수가 아닌 inline 함수이다. 호출에 따른 성능 저하가 없다.
// 단점: 정책 Class가 Function이 아닌 template 인자로 전달되므로,
//      Runtime에 정책을 교체하는 것이 불가능하다.
//      => 컴파일 할 때, 정책이 결정된다!!

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

// Inherence를 사용한 Policy-based Design
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