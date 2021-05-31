#include <iostream>
#include <iterator>
using namespace std;

template<typename T>
class eostream_iterator
{
private:
    ostream* stream;
    const char* delimiter;
public:
    eostream_iterator(ostream &os, const char* const delim = 0)
        : stream(std::addressof(os))
        , delimiter(delim)
    {}

    eostream_iterator& operator*() { return *this; }
    eostream_iterator& operator++() { return *this; }
    eostream_iterator& operator++(int) { return *this; }

    eostream_iterator& operator=(const T &v)
    {
        *stream << v;
        if (0 != delimiter) {
            *stream << delimiter;
        }
        return *this;
    }
};


int main()
{
    eostream_iterator<int> p(cout, ", ");

    *p = 10;    // (p.operatr*()).operator=(10)

    return 0;
}