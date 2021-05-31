#include <iostream>
#include <vector>
#include <list>
#include <iterator> // for advance()
using namespace std;

#if 0
struct input_iterator_tag   // empty class
{};

struct output_iterator_tag
{};

struct forward_iterator_tag
    : public input_iterator_tag
{};

struct bidirectional_iterator_tag
    : public forward_iterator_tag
{};

struct random_access_iterator_tag
    : public bidirectional_iterator_tag
{};


template<typename T>
class vector_iterator
{
public:
    using iterator_category = random_access_iterator_tag;
};

template<typename T>
class list_iterator
{
public:
    using iterator_category = bidirectional_iterator_tag;
};
#endif

template<typename T>
void eadvance_imp(T &p, int n,
                    random_access_iterator_tag) 
{
    cout << "random access iterator" <<endl;
    p = p + 5;   // not allowed for list
}

template<typename T>
void eadvance_imp(T &p, int n,
                    input_iterator_tag) 
{
    cout << "input iterator" <<endl;
    while ( n-- ) {
        ++p;
    }
}

template<typename T>
void eadvance(T &p, int n) 
{
    // iterator category에 따라 다른 함수 선택
    eadvance_imp(p, n,
                    typename T::iterator_category());
}

int main()
{
    /*/
    vector s = { 1,2,3,4,5,6,7,8,9,10 }; 
    /*/
    list s = { 1,2,3,4,5,6,7,8,9,10 };
    //*/
    auto p = begin(s);
    
    // iterator p를 5칸 전진!
    // p = p + 5;
    eadvance(p, 5);

    cout << *p <<endl;
    return 0;
}
