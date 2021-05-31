#include <iostream>
#include <thread>
using namespace std;

void foo()
{
    cout << "thread start!" <<endl;
    this_thread::sleep_for( 2s );
    cout << "thread end!" <<endl;
}
int main()
{
    thread t(&foo);

    /*/
    t.join();       // thread 종료 대기
    /*/
    t.detach();     // main thread가 종료되어 child thread도 즉시 종료
    //*/

    return 0;
}