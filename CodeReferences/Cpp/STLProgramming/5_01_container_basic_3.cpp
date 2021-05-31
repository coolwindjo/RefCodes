#include <iostream>
using namespace std;

#if 1
#include <string>
#else
class mytraits  : public char_traits<char>
{
private:
    /* data */
public:
};

template<   typename T,
            typename Traits = std::char_traits<T>,
            typename Allocator = std::allocator<T> >
class basic_string
{
private:
    T* buff;

    bool operator==(const basic_string &s)
    {
        /*/
        strcmp(buff, s.buff);
        /*/
        Traits::compare( buff, s.buff, sizeof(buff) );  // need to implement all the methods
        //*/
    }
};

using string = basic_string<char>;
using wstring = basic_string<wchar_t>;

#endif

struct ci_char_traits : public std::char_traits<char> {
    static char to_upper(char ch) {
        return std::toupper((unsigned char) ch);
    }
    static bool eq(char c1, char c2) {
         return to_upper(c1) == to_upper(c2);
     }
    static bool lt(char c1, char c2) {
         return to_upper(c1) <  to_upper(c2);
    }
    static int compare(const char* s1, const char* s2, std::size_t n) {
        while ( n-- != 0 ) {
            if ( to_upper(*s1) < to_upper(*s2) ) return -1;
            if ( to_upper(*s1) > to_upper(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, std::size_t n, char a) {
        auto const ua (to_upper(a));
        while ( n-- != 0 ) 
        {
            if (to_upper(*s) == ua)
                return s;
            s++;
        }
        return nullptr;
    }
};
using ci_string = basic_string<char, ci_char_traits>;

int main()
{
    /*/
    string s1 = "abcd";
    string s2 = "ABCD";
    /*/
    ci_string s1 = "abcd";
    ci_string s2 = "ABCD";
    //*/

    if (s1 == s2) {
        cout << "the same" <<endl;
    }
    else{
        cout << "different!" << endl;
    }

    return 0;
}


