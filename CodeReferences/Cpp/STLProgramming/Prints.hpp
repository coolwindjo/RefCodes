#include <iostream>
using namespace std;

template<typename T>
void show(const T &v)
{
    for (const auto &e : v ) {
        cout << e << ", ";
    }
    cout <<endl;
}
