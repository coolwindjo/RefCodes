#include <iostream>
#include <type_traits>
// #include <concepts>

#include <iterator>
#include <vector>
#include <list>

// advance 만들기
template<typename T>  requires std::input_iterator<T>
void advance(T& p, int N)
{
    std::cout << "moving with ++" << std::endl;
    while (N--) ++p;
}

template<typename T>  requires std::random_access_iterator<T>
void advance(T& p, int N)
{
    std::cout << "moving with +" << std::endl;
    p = p + N;
}

template<typename T>  requires std::random_access_iterator<T>
void sort(T first, T last)
{
    std::cout << "random" << std::endl;
}

template<typename T>  requires std::bidirectional_iterator<T>
void sort(T first, T last)
{
    std::cout << "bi-directional" << std::endl;
}

int main()
{
    std::vector<int>    v = { 1,2,3,4,5,6,7,8,9,10};    // Random access iterator, ++과 + 모두 가능
    // std::list<int>      v = { 1,2,3,4,5,6,7,8,9,10};    // Bi-directional iterator, ++, -- 만 가능

    auto p = v.begin();

    // p를 5칸 전진하고 싶다.
    // p = p + 5;  // vector 일 때는 OK, list라면 Error
    // ++p; ++p; ++p; ++p; ++p;    // 모두 OK 하지만, vector라면 너무 느림!
    advance(p, 5);  // 최선의 코드

    sort(v.begin(), v.end());   // vector 가면 OK, list는 error
                                // v.sort() 는 list

    return 0;
}

