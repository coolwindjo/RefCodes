#include <vector>

template<typename T>
class List
{
public:
    List() {}
    List(std::size_t sz, T value) {}
    /*/
    template<typename C> List(const C& c) {}
    /*/
    template<typename C> List(C&& c) {}     // forwarding reference
    //*/
    ~List() {}
};

// Clas Template type deduction guide
// Constructor 모양 => List<Type>
List()->List<int>;      // not recommended
/*/
template<typename C> List(const C& c)->List< typename C::value_type >;
/*/
#if 0
template<typename C> List(C&& c)->List< typename C::value_type >;   // error: reference type
#else
    #if 0
template<typename C> List(C&& c)->List< typename std::remove_reference_t<C>::value_type >;  // C++17
    #else
template<typename C> List(C&& c)->List< typename std::ranges::range_value_t<C> >;           // C++20
    #endif
#endif
//*/

int main()
{
    List<int>   s1(10, 3);
    List        s2(10, 3);    // C++17 부터는 Class Template도 Template 인자 추론 가능
    List        s3;

    std::vector v = {1,2,3};
    List s4(v);

    return 0;
}
