#include <iostream>
#include <memory>
using namespace std;

int main()
{
    unique_ptr<int> up(new int(42));

    cout << "up.get()   = " << up.get() <<endl;
    cout << "*up        = " << *up      <<endl;

#if 1
    /*/
    auto sp( make_shared<int>(move(up)) );
    /*/
    // shared_ptr<int> sp(move(up));
    shared_ptr<int> sp{move(up)};
    //*/
    cout << "-----After move-----" <<endl;

    cout << "sp.get()   = " << sp.get() <<endl;
    cout << "*sp        = " << *sp      <<endl;
    cout << "up.get()   = " << up.get() <<endl;
    cout << "*up        = " << *up      <<endl;
#endif 

    return 0;
}