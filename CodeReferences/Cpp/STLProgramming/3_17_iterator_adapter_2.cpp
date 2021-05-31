#include <iostream>
#include <list>
using namespace std;

template<typename Iter>
class ereverse_iterator
{
private:
    Iter iterator;              // list의 일반 iterator ++ =>   
public:
    ereverse_iterator(Iter it)
        : iterator(it)
    {
        --iterator;
    }

    ereverse_iterator& operator++()
    {
        --iterator;
        return *this;
    }

    typename Iter::value_type operator*()
    {
        return *iterator;
    }

    // ==, !=, --(++)
};


int main()
{
    list<int> s = { 1,2,3,4,5,6,7,3,9,10 };

    auto p1 = end(s);

    ereverse_iterator< list<int>::iterator > p2 (p1);

    ++p2;

    cout << *p2 <<endl;     // 9

    ++p2;

    cout << *p2 <<endl;     // 3

    return 0;
}