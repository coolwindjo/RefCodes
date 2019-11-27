#include <iostream>

using namespace std;

class Base
{
    // Access specifier.
public:
    int pub;
protected:
    int pro;
private:
    int pri;
};

// 1. Private acccessing of the Parent class does not affected.
// 2. protected inherence
//      1) protected    -> protected
//      2) public       -> protected
// 3. private inherence
//      1) protected    -> private
//      2) public       -> private

            // : <Access Modifier> Base
class Derived : public Base
{
};

int main()
{
    // Base b; b.pub = 10;
    Derived d; d.pub = 10;
    system("pause");
    return 0;
}