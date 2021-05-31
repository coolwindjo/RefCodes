#include <iostream>
#include <queue>
#include <vector>
#include <functional>   // for greater<int>
using namespace std;

#if 0
template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::less<typename Container::value_type>
        > class priority_queue
#endif

struct abs_greater
{
    bool operator()(int a, int b) const
    {
        return abs(a) > abs(b);
    }
};

int main()
{
    /*/
    priority_queue< int, vector<int>, greater<int> > pq;
    /*/
    priority_queue< int, vector<int>, abs_greater > pq;
    //*/

    pq.push(10);    // <
    pq.push(20);
    pq.push(-15);
    pq.push(12);

    cout << pq.top() <<endl;    // 20   10
    pq.pop();
    cout << pq.top() <<endl;    // 15   12

    return 0;
}