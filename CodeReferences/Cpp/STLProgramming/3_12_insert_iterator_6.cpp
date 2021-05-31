#include <iostream>
#include <list>
using namespace std;

template<typename C>
class einsert_iterator
{
private:
    // C : list<int>
    C* container;
    typename C::iterator iterator;
public:
    explicit einsert_iterator(C &c, typename C::iterator &it)
        : container(std::addressof(c)), iterator(it) {}

    einsert_iterator& operator*() { return *this; }                // check this out!
    einsert_iterator& operator++() { return *this; }               // for ++p
    einsert_iterator& operator++(int) { return *this; }            // for p++
    einsert_iterator& operator=(const typename C::value_type &a)   // check this out!
    {
        container->insert(iterator, a);
        return *this;
    }
    einsert_iterator& operator=(const typename C::value_type &&a)   // check this out!
    {
        container->insert(iterator, move(a));
        return *this;
    }
};

int main()
{
    list<int> s = { 1,2 };

    einsert_iterator< list<int> > p(s, ++begin(s));

    *p = 30;    // ( p.operator*() ).operator=(30)

    int x[2] = { 1,2 };
    copy( x, x+2, p );  // ++p

    for (auto &n : s) {
        cout << n << ", ";
    }

    return 0;
}