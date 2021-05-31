#include <iostream>
#include <list>
#include <vector>

using namespace std;

#if 0
void print(vector<int>& c)
#else
template<typename T>
    #if 0
    void print(vector<T> &c)
    #else
    void print(const T &c)
    #endif
#endif
{
    // T : list<double>
    // T::value_type => list<double>::value_type
    // typename : value_type을 Type의 이름으로 해석
    typename T::value_type n = c.front();
    cout << n <<endl;
}

#if 0
    template<typename T>
    class list
    {
    public:
    #if 0
        typedef T value_type;   // 핵심!
    #else
        using value_type = T;   // C++11
    #endif
    };
#endif


int main()
{
    /*/
    vector<int> v = {1,2,3};
    vector<double> v = {1,2,3};
    /*/
    list<double> v = {1,2,3};
    //*/
    print(v);
    
    return 0;
}