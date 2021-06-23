#include <iostream>
#include <algorithm>
#include <vector>


// template<typename Iter, typename T> requires std::predicate<T, int>
// template<typename Iter, typename T> requires std::predicate<T, typename Iter::value_type>
// template<typename Iter, typename T> requires std::predicate<T, std::iterator_traits<Iter>::value_type>
template<typename Iter, typename T> requires std::predicate<T, std::iter_value_t<Iter> >
void find(Iter first, Iter last, T value)
{
    std::cout<< "search with condition" <<std::endl;
}

// template<typename Iter, typename T> requires (!std::predicate<T, typename Iter::value_type>)
template<typename Iter, typename T> requires (!std::predicate<T, std::iter_value_t<Iter> >)
void find(Iter first, Iter last, T value)
{
    std::cout<< "search the value" <<std::endl;
}

int main()
{
    // std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    int v[10] = {1,2,3,4,5,6,7,8,9,10};

    // auto p1 = std::find(v.begin(), v.end(), 3);
    // auto p2 = std::find_if(v.begin(), v.end(), [](int n){return n%2==0;});

    // auto p1 = find(v.begin(), v.end(), 3);
    // auto p2 = find(v.begin(), v.end(), [](int n){return n%2==0;} );

    // v.begin() 보다 std::begin(v)이 더 좋습니다. (더 general 한 format)
    // 
    find(std::begin(v), std::end(v), 3);
    find(std::begin(v), std::end(v), [](int n){return n%2==0;} );
    
    return 0;
}
