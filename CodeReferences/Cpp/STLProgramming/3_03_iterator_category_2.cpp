#include <forward_list>
#include <list>
using namespace std;

int main()
{
    /*/
    forward_list s1 = { 1,2,3 };    // error for --p;
    /*/
    list s1 = { 1,2,3 };
    //*/
    auto p = begin(s1);

    ++p;
    --p;    // ??

    return 0;
}