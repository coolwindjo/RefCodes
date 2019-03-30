// Smart Pointer
#include <iostream>
using namespace std;

class Car
{
public:
    Car() { cout << "Resource allocation" << endl; }
    ~Car() { cout << "Resource free" << endl; }

    void go() { cout << "A car goes." << endl; }
};

int main()
{
    Car* p = new Car;
    p->go();
    (*p).go();
    delete p;

    system("pause");
    return 0;
}