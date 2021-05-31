#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
using namespace std;

int main()
{
    map< string, list<int> > index;

    ifstream f("text.txt");
    int line_no = 0;
    string s;

    while (getline(f, s)) {
        line_no++;
        istringstream iss(s);
        string word;
        while (iss >> word) {
            index[word].push_back(line_no);
        }
    }
    // ----------------------------------------
    auto p = begin(index);

    while (end(index) != p) {
        cout << p->first << " : ";  // 단어 출력
        for ( auto &n : p->second ) {
            cout << n << ", ";
        }
        cout <<endl;
        ++p;
    }

    return 0;
}