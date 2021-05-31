#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct FindChar
{
    string data;
    FindChar(string s) : data(s) {}

    bool operator()(char c) const
    {
        auto p = find( begin(data), end(data), c );
        return p != end(data);
    }
};

int main()
{
    vector<string> v;

    ifstream f("5_05_vector_4.cpp");

    string s;

    /*/
    f >> s;
    /*/
    while (getline(f, s))
    //*/
    {
        v.push_back(s);
    }

    // -------------------------------------------
    /*/
    reverse( begin(v), end(v) );
    /*/
    for (int i=0; i<v.size(); ++i) {
#if 0
        reverse( begin(v[i]), end(v[i]) );
#else
    #if 0
        replace( begin(v[i]), end(v[i]), 'i', ' ' );
    #else
        #if 0
        // 모든 모음을 공백 치환
        replace_if( begin(v[i]), end(v[i]),
                    [](char c){
                        return (c=='a')
                        || (c=='e')
                        || (c=='i')
                        || (c=='o')
                        || (c=='u')
                        ;
                    },
                    ' ' );
        #else
        /*/
        FindChar fc("0123456789");
        /*/
        FindChar fc("aeiouAEIOU");
        //*/
        replace_if( begin(v[i]), end(v[i]), fc, ' ');
        #endif
    #endif
#endif
    }
    //*/
    // -------------------------------------------

    for (auto str : v) {
        cout << str <<endl;
    }
    
    return 0;
}