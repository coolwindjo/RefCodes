#include <iostream>
#include <list>
using namespace std;

#include <filesystem>  // directory_iterator
using namespace std::filesystem;

int main()
{
    int x[5] = { 1,2,3,4,5 };

    int* p = x;
    cout << *p <<endl;
    ++p;
    
    list<int> s = { 1,2,3,4,5 };
    list<int>::iterator it = s.begin();
    cout << *it <<endl;
    ++it;

    directory_iterator dp("../");

    cout << *dp <<endl;
    ++dp;
    cout << *dp <<endl;
    return 0;
}