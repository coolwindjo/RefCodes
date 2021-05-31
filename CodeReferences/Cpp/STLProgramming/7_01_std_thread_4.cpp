#include <iostream>
#include <thread>
#include <functional>
using namespace std;

/*/
void f1(int a, int b)
/*/
void f1(int a, int &b)
//*/
{
    b = 30;
}

int main()
{
    /*/
    thread t1(&f1, 1, 2);
    thread t2( bind(&f1, 1, 2) );

    t1.join();
    t2.join();
    /*/
    int n = 10;
    thread t1( bind(&f1, 1, ref(n)) );

    t1.join();
    //*/

    cout << n <<endl;   // 30

    return 0;
}