#include <iostream>
#include <memory>
using namespace std;

class Car
{
private:
    int color;
public:
    explicit Car(/* args */) {cout<<"Car()"<<endl;}
    virtual ~Car() {cout<<"~Car()"<<endl;}

    void Go(void) {cout<<"Car go"<<endl;}
};

int main()
{
    /*/
    Car* p = new Car;
    /*/
    shared_ptr<Car> p( new Car );
    //*/

    p->Go();    // p.operator->()
    (*p).Go();  // p.operator*()

    // delete p;

    return 0;
}
