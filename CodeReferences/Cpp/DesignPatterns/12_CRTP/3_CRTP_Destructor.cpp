#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
    Base();
    void finalize()
    {
        delete static_cast<T*>(this);
    }

protected:
    ~Base();
    //virtual ~Base();

private:

};

template <typename T>
Base<T>::Base()
{
}

template <typename T>
Base<T>::~Base()
{
    cout << "Base destructor called" << endl;
}


// Derived Class
class Derived : public Base<Derived>
{
public:
    Derived();
    ~Derived();

private:

};

Derived::Derived()
{
}

Derived::~Derived()
{
    cout << "Derived destructor called" << endl;
}


int main()
{
    Base<Derived>* p = new Derived;
    //delete p;
    //delete static_cast<Derived*>(p);
    p->finalize();

    system("pause");
    return 0;
}