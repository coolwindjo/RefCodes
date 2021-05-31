#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T, int N>
struct Array
{
    T buf[N];

    typedef T* iterator;

    iterator begin() { return buf; }
    iterator end() { return buf + N; }

    int size() const { return N; }

    T& operator[](int n) { return buf[n]; }
};

int main()
{
    Array<int, 5> arr = { 1,2,3,4,5 };

    // auto p = find( ++begin(arr), end(arr), 3 ); // error!
    auto p = find( next(begin(arr)), end(arr), 3 );

    cout << *p <<endl;

    return 0;
}
