#include <iostream>

class Car
{
private:
    int color;
    int speed;
public:
    explicit Car(int c=0, int s=0) : color(c), speed(s) {std::cout<<"Car()"<<std::endl;}
    virtual ~Car() {std::cout<<"~Car()"<<std::endl;}
    void Go(void) {std::cout<<"Car Go!"<<std::endl;}
};
