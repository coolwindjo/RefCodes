#include <iostream>
#include <thread>
using namespace std;

void f1()      {}
void f2(int a) {}

struct Worker
{
    void Main() {}
};

struct Functor
{
    void operator()() {}
};

int main()
{
    // 1. Function Pointer
    thread t1(&f1);

    // 2. Function Pointer with arguments
    thread t2(&f2, 5);

    // 3. Member method
    Worker w;
    thread t3(&Worker::Main, &w);

    // 4. Function Object
    Functor f; f();
    thread t4(f);

    // 5. Lambda expression
    thread t5( [](){cout<<"thread t5"<<endl;} );


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}