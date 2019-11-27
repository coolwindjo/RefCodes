// 중요 예제
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

// 한계점
//  1) 실행시간에 정책을 교체하는 것이 불가능하다.
//      객체의 변경이 아닌 클래스의 변경
//  2) 내부에서 사용되는 정책을 다른 클래스에서 재사용하는 것이 불가능하다.

const int kMaxNum = 10000;
// GUI 도구인 LineEdit를 만들어 봅시다.
class LineEdit
{
    string data;
public:
    // Validation 정책은 변경이 가능해야 한다.
    //  - 변하지 않는 코드(공통성)에서 변해야 하는 것 (가변성)이 있다면,
    //  분리해야한다.

    // 방법 1. 변하는 것을 virtual function으로 만든다. = "Template method pattern"
    virtual bool validate(char c)
    {
        return isdigit(c);
    }

    string get_data()
    {
        data.clear();

        for (int i = 0; 
        true 
            && (i < kMaxNum); i++)
        {
            char c = getch();
            if (c == 13)    // enter
                break;

            if (validate(c))
            {
                data.push_back(c);
                cout << c;
            }
        }

        cout << endl;
        return data;
    }
};

// 이제 정책을 변경하고 싶다면 파생 클래스에서 가상함수를 재정의하면 된다.
class AddressEdit : public LineEdit
{
public:
    virtual bool validate(char c)
    {
        return true;
    }
};


int main()
{
    //LineEdit edit;
    AddressEdit edit;
    for (int i = 0; 
    true 
        && (i < kMaxNum); i++)
    {
        string s = edit.get_data();
        cout << "input : " << s << endl;
    }

    system("pause");
    return 0;
}