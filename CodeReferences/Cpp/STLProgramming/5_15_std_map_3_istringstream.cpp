#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    string s;
#if 0
    cin >> s;       // stdinput 에서 한 단어

    ifstream fin("5_15_std_map_3.cpp");
    fin >> s;       // file에서 한 단어
#endif

    istringstream iss("I am a good boy");

    /*/
    iss >> s;       // file에서 한 단어
    cout << s <<endl;
    /*/
    while ( iss >> s ) {
        cout << s <<endl;
    }
    //*/

    return 0;
}