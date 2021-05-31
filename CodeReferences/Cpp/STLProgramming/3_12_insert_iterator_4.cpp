#include <iostream>
#include <list>
using namespace std;

template<typename C>
class eback_insert_iterator
{
private:
    // C : list<int>
    C* container;
public:
    eback_insert_iterator(C &c) : container(&c) {}

    eback_insert_iterator&                      // check this out!
    operator*() { return *this; }

    eback_insert_iterator&
    operator=(const typename C::value_type &a)  // check this out!
    {
        container->push_back(a);
        return *this;
    }
};

int main()
{
    list<int> s = { 1,2 };

    eback_insert_iterator< list<int> > p(s);

    p = 20;     // 이것도 가능하지만, 모든 iterator는 dereferencing이 가능 해야하므오 아래 style을 default로 함
    *p = 30;    // ( p.operator*() ).operator=(30)

    for (auto &n : s) {
        cout << n << ", ";
    }

    return 0;
}