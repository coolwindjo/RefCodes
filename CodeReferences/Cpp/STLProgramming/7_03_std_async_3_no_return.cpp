#include <iostream>
#include <thread>
#include <future>   // for async
using namespace std;

int f1()
{
    this_thread::sleep_for( 3s );
    cout << "f1 end!" <<endl;
    return 10;
}

int main()
{
    /*/
    future<int> ft = async( launch::async, &f1 );
    /*/
    async( launch::async, &f1 );    // Return 값으로 future<int> 임시 객체
    //*/

    cout << "main routine" <<endl;

    // cout << ft.get() <<endl;        // 여기서 대기

    return 0;
}