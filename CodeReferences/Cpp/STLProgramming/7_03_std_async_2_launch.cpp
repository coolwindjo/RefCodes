#include <iostream>
#include <thread>
#include <future>   // for async
using namespace std;

int f1()
{
    cout << "f1: " <<this_thread::get_id() <<endl;
    this_thread::sleep_for( 3s );
    return 10;
}

int main()
{
    cout << "main: " << this_thread::get_id() <<endl;

#if 0
    future<int> ft = async( launch::async, &f1 );
#else
    #if 0
    // f1 을 ft.get() 호출 할 때 실행
    future<int> ft = async( launch::deferred, &f1 );
    #else
    // f1 을 가능혀면 thread로 실행해주고, thread가 지원되지 않으면 defferrd 적용!
    future<int> ft = async( launch::deferred | launch::async, &f1 );
    #endif
#endif

    this_thread::sleep_for( 1s );

    cout << "main routine" <<endl;

    cout << ft.get() <<endl;        // 여기서 대기

    return 0;
}