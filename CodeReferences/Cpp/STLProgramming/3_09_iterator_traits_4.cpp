#include <iostream>
#include <vector>
#include <list>
#include <iterator> // for advance()
using namespace std;

#if 0
template<class T>
struct iterator_traits
{
    using iterator_category = typename T::iterator_category;
    using value_type = typename T::value_type;
    using difference_type = typename T::difference_type;
    using pointer = typename T::pointer;
    using reference = typename T::reference;
};

template<class T>
struct iterator_traits<T*>
{
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
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
                    /*/
                    typename T::iterator_category());   // error @ s[10]
                    /*/
                    typename iterator_traits<T>::iterator_category());
                    //*/
}

int main()
{
    /*/
    vector s = { 1,2,3,4,5,6,7,8,9,10 }; 
    /*/
    int s[10] = { 1,2,3,4,5,6,7,8,9,10 };
    //*/
    auto p = begin(s);
    
    // iterator p를 5칸 전진!
    // p = p + 5;
    eadvance(p, 5);

    cout << *p <<endl;
    return 0;
}
