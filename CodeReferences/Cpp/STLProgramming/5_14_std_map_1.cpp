#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    map<string, string> m;

    // 1. pair 만들어서 insert
    pair<string, string> p1("월요일", "Monday");
    m.insert( p1 );

    // 2. make_pair
    m.insert( make_pair("화요일", "Tuesday"));

    // 3. [] operator
    m["수요일"] = "Wednesday";

    cout << m["월요일"] <<endl; // "Monday"
    cout << m["토요일"] <<endl; // make_pair("토요일", "") 항목 추가

    for ( auto day : m ) {
        cout << day.first << ":" << day.second <<endl;
    }

    auto ret = m.find("일요일");
    if (m.end() == ret) {
        cout << "failed to search!" <<endl;
    }
    return 0;
}