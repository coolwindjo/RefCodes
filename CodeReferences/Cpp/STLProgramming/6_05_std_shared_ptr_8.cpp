#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct People
{
    string name;
    /*/
    shared_ptr<People> bf;
    /*/
    People* bf;     // Raw pointer won't count up the use count.
                    // 단점: 대상 객체가 파괴되었는지 알 수 없다.   => weak_ptr
    //*/

    People(string s) : name(s) {}
    ~People() {cout<<"~People(): "<<name<<endl;}
};

int main()
{
    shared_ptr<People> p1(new People("KIM"));
    {
        shared_ptr<People> p2(new People("LEE"));

#if 1
        /*/
        p1->bf = p2;
        p2->bf = p1;
        /*/
        p1->bf = p2.get();
        p2->bf = p1.get();
        //*/
#endif 
    }   // p2 파괴

    if (nullptr != p1->bf) {
        cout << p1->bf->name <<endl;    //
    }

    cout << "-----------------------" <<endl;

    return 0;
}
