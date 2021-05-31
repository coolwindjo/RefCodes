#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

// Tag Dispatching 기술 정리 - "C++ Tempalte Programming 과정" 참고

#if 0
// 1. 함수 인자를 사용한 Overloading
template<typename T>
void eadvance_imp(T &p, int n,
                    random_access_iterator_tag) 
{
    cout << "random access iterator" <<endl;
    p = p + n;   // not allowed for list
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
#else
    #if 0
    // 2. C++17 if constexpr 사용
    #include <type_traits>
    template<typename T>
    void eadvance(T &p, int n)
    {
        if constexpr (is_same<typename T::iterator_category, random_access_iterator_tag>::value)
        {
            p = p + n;
        }
        else {
            while ( n-- ) {
                ++p;
            }
        }
    }
    #else
    // 3. enable_if 사용 => SFINAE 개념 사용
    #include <type_traits>
    template<typename T>
    typename enable_if<is_same<typename T:: iterator_category, random_access_iterator_tag>::value>::type 
    eadvance(T &p, int n)
    {
        p = p + n;
    }

    template<typename T>
    typename enable_if< !is_same<typename T:: iterator_category, random_access_iterator_tag>::value>::type 
    eadvance(T &p, int n)
    {
        while ( n-- ) {
            ++p;
        }
    }
    #endif
#endif

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
