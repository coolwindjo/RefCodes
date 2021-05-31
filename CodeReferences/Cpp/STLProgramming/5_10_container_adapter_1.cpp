#include <iostream>
#include "MyAlloc2.hpp"
using namespace std;

// list 가 제공된다.
#include <list>
#include <vector>
#include <deque>

// 그런데 stack 이 필요하다.
#if 0
#include <stack>    // stack adapter
#else
template< typename T, typename C=deque<T> >
class stack
{
private:
    /*/
    list<T> st;
    /*/
    C st;
    //*/
public:
    inline void push(const T &a)   {st.push_back(a);}
    inline void pop(void)          {st.pop_back();} 
    inline T& top(void)            {return st.back();}
    inline bool empty(void)        {return st.empty();}
};
#endif

int main()
{
    stack< int > s2;
    stack< int, vector<int> > s1;
    stack< int, list<int> > s;
    stack< int, list<int, MyAlloc<int>> > s3;
    s.push(10);
    s.push(20);

    cout << s.top() <<endl; // 20
    s.pop();
    
    cout << s.top() <<endl; // 10

    return 0;
}