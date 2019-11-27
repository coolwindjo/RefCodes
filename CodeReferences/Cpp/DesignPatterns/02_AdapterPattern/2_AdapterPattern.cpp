#include <iostream>
using namespace std;

// list is already present.
#include <list>

// but, client require a stack.
// 2. reuse the list to make a stack.

// Adapter pattern : 기존 클래스의 인터페이스(함수 이름)을 변경해서
//                  사용자가 요구하는 새로운 클래스 처럼 보이게 하는 패턴

// Library는 쉽게 사용할 수 있도록 만들어야 하고,
// 잘못 사용하기 어렵게 만들어야 한다.

// private inherence : 부모 클래스로부터 구현은 물려 받지만, (자식이 내부적으로 사용하지만)
//                      인터페이스는 물려 받지 않겠다. (부모함수를 외부로 노출하지 않겠다.)

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