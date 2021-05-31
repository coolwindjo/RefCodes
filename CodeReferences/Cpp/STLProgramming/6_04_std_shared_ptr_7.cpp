#include <iostream>
#include <memory>
#include <thread>
#include "Car.hpp"
using namespace std;

class Worker : public enable_shared_from_this<Worker>   // CRTP
{
private:
    Car c;
    shared_ptr<Worker> holdMe;
public:
    // /*/  
    void Run()
    {
        holdMe = shared_from_this();
    /*/
    void Run( shared_ptr<Worker> p )
    {
        // holdMe = this;      // Bug: create another control block while taking a raw pointer
        holdMe = p;
    //*/

        thread t(&Worker::Main, this);
        t.detach();
    }

    void Main()
    {
        c.Go();     // Member data (Car) 사용
        cout << "Finish thread" <<endl;

        holdMe.reset();
    }
};

int main()
{
    {
        shared_ptr<Worker> sp = make_shared<Worker>();
        // /*/
        sp->Run();
        /*/
        sp->Run(sp);
        //*/
    }
    getchar();

    return 0;
}
