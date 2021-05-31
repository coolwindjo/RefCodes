#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>    // stack adapter
#include <queue>
using namespace std;

int main()
{
    stack<int> s1;   // deque
    stack<int, vector<int>> s2;
    stack<int, list<int>> s3;
    s1.push(10);
    s1.pop();
    s1.top();

    queue<int> q1;
    q1.push(10);
    q1.pop();
    q1.front();
    queue<int, vector<int>> q2;     // error!
    q2.push(10);
    // q2.pop();                       // error! 지연된 instance화
    queue<int, list<int>> q3;

    priority_queue<int> pq;

    return 0;
}