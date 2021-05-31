#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <forward_list>
#include <array>
#include "Prints.hpp"
using namespace std;

int main()
{
    /*/
    list<int> s;        // error with s[0]
    /*/
    // vector<int> s;   error with push_front()
    deque<int> s;
    //*/

    s.push_front(10);
    s.push_back(20);

    cout << s[0] <<endl;

    show(s);

    return 0;
}