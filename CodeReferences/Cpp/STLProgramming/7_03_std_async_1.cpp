#include <iostream>
#include <thread>
#include <future>   // for async
using namespace std;

int f1()
{
    this_thread::sleep_for( 3s );
    return 10;
}

int main()
{
    /*/
    thread t(&f1);
    t.join();
    /*/
    future<int> ft = async( launch::async, &f1 );
    //*/

    cout << "main routine" <<endl;

    // cout << ft.get() <<endl;        // thread 종료 대기  => join() 이 필요 없어짐

    return 0;
}