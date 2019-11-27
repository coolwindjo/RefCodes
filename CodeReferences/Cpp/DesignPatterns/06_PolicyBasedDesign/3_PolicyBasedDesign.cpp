#include <iostream>
using namespace std;

class MyTraits : public char_traits<char>
{
public:
    static bool compare(const char* a, const char* b, size_t sz)
    {
        return _strcmpi(a, b);
    }
};

// basic_string
typedef basic_string<char, MyTraits> MyString;

int main()
{
    //string s1 = "abcd";
    //string s2 = "ABCD";
    MyString s1 = "abcd";
    MyString s2 = "ABCD";

    if (s1 == s2)
    {
        cout << "same" << endl;
    }
    else
    {
        cout << "not same" << endl;
    }

    system("pause");
    return 0;
}