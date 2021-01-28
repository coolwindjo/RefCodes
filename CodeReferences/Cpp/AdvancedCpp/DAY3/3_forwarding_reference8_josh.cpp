// #include <iostream>
#include <vector>
#include <type_traits>

template<typename T> class List
{
private:
    /* data */
public:
    List(int sz, T value) {}
    ~List() {}

    template<typename C>
    // List(C c){} // call by value: 복사본의 Overhead
    // List(C& c){} // call by reference: 임시객체를 받을 수 없다.
    // List(const C& c){}  // const lvalue reference: 임시객체를 받을 수 있지만,
                        // "move" 가 안됨
    List(C&& c) {}
};

template<typename C>
// List(C&& c)->List<typename C::value_type>;  // vector<int>&::value_type 하는 Code라서 Error
List(C&& c)->List< typename std::remove_reference_t<C>::value_type >;

int main()
{
    List s1(10, 3);

    std::vector<int> v = {1,2,3};
    List s2(v); // v 는 lvalue 이므로,
                // C의 Type은 "vector<int>" 가 아니고, "vector<int>&" 입니다.

    List s3(std::vector<int>{1,2,3});   // 임시 객체
    return 0;
}