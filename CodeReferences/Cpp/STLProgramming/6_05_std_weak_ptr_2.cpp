#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct People
{
    string name;
    weak_ptr<People> bf;

    People(string s) : name(s) {}
    ~People() {cout<<"~People(): "<<name<<endl;}
};

int main()
{
    shared_ptr<People> p1(new People("KIM"));
    {
        shared_ptr<People> p2(new People("LEE"));

        p1->bf = p2;
        p2->bf = p1;
    }   // p2 파괴

    if ( !p1->bf.expired() ) {
        shared_ptr<People> sp2 = p1->bf.lock();
        if ( nullptr != sp2 ) {
            cout << sp2->name <<endl;
        }
        else {
            cout << "bf is destoryed" <<endl;
        }
    }

    cout << "-----------------------" <<endl;;

    return 0;
}
