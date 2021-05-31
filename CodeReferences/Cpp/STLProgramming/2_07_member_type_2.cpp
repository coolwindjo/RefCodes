#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename T>
typename T::value_type sum(const T &first, const T &last)
{
    typename T::value_type s = 0;

    T elem = first;

    while (last != elem){
        s += *elem++;
    }

    return s;
}

int main()
{
    list<int> s = {1,2,3};

    int val = sum(s.begin(), s.end());

    cout << val <<endl;

    return 0;
}