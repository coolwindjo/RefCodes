#include <iostream>
#include <string>
#include <type_traits>

template<typename T, typename U> struct pair
{
    T first;
    U second;
    // pair(const T& a, const U& b) : first(a), second(b) {}
    // pair(T&& a, U&& b) : first(std::move(a)) {}

    // setData 의 경우, 인자가 한 개 이므로 2개의 setter를 제공함녀 되지만,
    // pair의 경우, 4개의 생성자 필요!

    // "forwarding reference" 가 좋다!
    template<typename A, typename B>
    pair(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}
};

int main()
{
    std::string s1 = "ABCD";
    std::string s2 = "ABCD";

    pair<std::string, std::string> p1(s1, std::move(s2));

    // pair<std::string, std::string> p2(1, 3.4);  // 이 경우의 현상을 생각해 봅시다.

    std::cout<< s1 <<std::endl; // "ABCD"
    std::cout<< s2 <<std::endl; // ""
    return 0;
}
