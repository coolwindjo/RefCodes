#include <iostream>
#include <thread>
#include <string>
#include <mutex>    // for mutex
using namespace std;

int global = 0;
mutex m;
// timed_mutex m;
// recursive_mutex m;
// recursive_timed_mutex m;
// shared_mutex m;
// shared_timed_mutex m;

void f1()
{
    lock_guard<mutex> lg(m);    // Constructor 에서 m.lock
    // m.lock();
    global = 100;
    global = global + 1;
    // m.unlock();

    // Exception 이 일어나더라도 lock_guard는 파괴됨
}

int main()
{
    thread t1(&f1);
    thread t2(&f1);

    t1.join();
    t2.join();

    return 0;
}