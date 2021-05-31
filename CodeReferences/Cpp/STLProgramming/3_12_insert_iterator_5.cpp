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
#if 0   // 2018년도에는 g++에서 필요 했었음
    // int n = *i; // input
    // *i = 20;    // output
    using iterator_category = output_iterator_tag;

    // container이므로 value_type 비롯한 것들은 void
    using value_type = void;
    using pointer = void;
    using reference = void;
    using difference_type = void;

    using container_type = C;
#endif

#if 0
    explicit eback_insert_iterator(C &c) : container(&c) {}     // c.operator&() 가 private으로 막혀 있는 경우가 있음
#else
    explicit eback_insert_iterator(C &c) : container(std::addressof(c)) {}
#endif

    eback_insert_iterator& operator*() { return *this; }                // check this out!
    eback_insert_iterator& operator++() { return *this; }               // for ++p
    eback_insert_iterator& operator++(int) { return *this; }            // for p++
    eback_insert_iterator& operator=(const typename C::value_type &a)   // check this out!
    {
        container->push_back(a);
        return *this;
    }
    eback_insert_iterator& operator=(const typename C::value_type &&a)   // check this out!
    {
        container->push_back(move(a));
        return *this;
    }
};

int main()
{
    list<int> s = { 1,2 };

    eback_insert_iterator< list<int> > p(s);

    *p = 30;    // ( p.operator*() ).operator=(30)

    int x[2] = { 1,2 };
    copy( x, x+2, p );  // ++p

    for (auto &n : s) {
        cout << n << ", ";
    }

    return 0;
}