#include <iostream>
#include <list>

using namespace std;

template<typename T>
class List
{
public:
    List(int size, T initVal) {}
};

int main()
{
    List<int>   s1(10, 0);
    List        s2(10, 0);  // C++17

    list<int>   s3(10, 0);
    list        s4(10, 0);  // C++17

    return 0;
}
