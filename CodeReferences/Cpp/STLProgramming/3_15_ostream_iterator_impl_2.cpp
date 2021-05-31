#include <iostream>
#include <iterator>
using namespace std;

template< typename T, typename CharT = char, typename Traits = char_traits<CharT> >
class eostream_iterator
{
private:
    /*/
    ostream* stream;
    /*/
    basic_ostream< CharT, Traits >* stream;
    const CharT* delimiter;
public:
    eostream_iterator(ostream &os, const CharT* const delim = 0)
        : stream(std::addressof(os))
        , delimiter(delim)
    {}

    using iterator_category = output_iterator_tag;
    using value_type = void;
    using pointer = void;
    using reference = void;
    using difference_type = void;
    // defined as above in the ostream_iterator reference

    using char_type = CharT;
    using traits_type = Traits;
    using ostream_type = basic_ostream< CharT, Traits >;
    // These are picked out!

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