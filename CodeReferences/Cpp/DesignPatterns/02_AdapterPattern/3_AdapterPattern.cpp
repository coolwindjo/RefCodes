#include <iostream>

#include <list>
#include <vector>
#include <deque>

using namespace std;

// S/W의 재사용은 상속과 포함이 있다. => 포함이 좋을 때가 많다.

#include <stack>
#if 0
template <typename T, typename C = deque<T>>
class stack
{
    C st;
public:
    void push(const T& a)
    {
        st.push_back(a);
    }
    void pop(void)
    {
        st.pop_back();
    }
    T& top(void)
    {
        return st.back();
    }
};
#endif

int main()
{
    stack<int, list<int>> s;
    stack<int, vector<int>> s2;

    s.push(10);
    s.push(20);

    cout << s.top() << endl;

    system("pause");
    return 0;
}