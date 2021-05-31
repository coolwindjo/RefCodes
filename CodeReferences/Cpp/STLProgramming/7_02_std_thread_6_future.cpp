#include <iostream>
#include <thread>
#include <future>   // for promise<>
using namespace std;

void f1( promise<int> &p )
{
    this_thread::sleep_for( 3s );
    p.set_value(10);
}

int main()
{
    promise<int> p;
    future<int> ft = p.get_future();

    thread t(&f1, ref(p));

    cout << "Wait for the value ... " <<endl;
    cout << "value: " << ft.get() <<endl;   // 여기서 대기

    t.join();

    return 0;
}