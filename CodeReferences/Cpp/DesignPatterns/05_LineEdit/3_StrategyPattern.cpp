// 중요 예제
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

// 공통성과 가변성을 분리하는 
// 방법 2. 변하는 것을 Interface based Class로 분리한다. (Strategy Pattern)
// 장점
//  1) 실행시간에 정책을 교체하는 것이 가능하다.
//  2) 내부에서 사용되는 정책을 다른 클래스에서 재사용하는 것이 가능하다.

// Qt라는 오픈 소스 GUI 라이브러리에는 QValidator라는 Interface가 있습니다.

const int kMaxNum = 10000;

struct IValidator
{
    virtual bool validate(string s, char c) = 0;
    virtual bool is_complete(string s)
    {
        return true;
    }
    ~IValidator() {}
};

// GUI 도구인 LineEdit를 만들어 봅시다.
class LineEdit
{
    string data;
    //-----------------
    IValidator* pValidator;

public:
    LineEdit() :pValidator(0){}

    void set_validator(IValidator* p) 
    {
        pValidator = p;
    }
    //-----------------

    string get_data()
    {
        data.clear();

        for (int i = 0; i < kMaxNum; i++)
        {
            char c = _getch();
            if (c == 13 && (pValidator == 0 || pValidator->is_complete(data)))    // enter
                break;

            if (pValidator == 0 || pValidator->validate(data, c))
            {
                data.push_back(c);
                cout << c;
            }
        }

        cout << endl;
        return data;
    }
};

// 이제 다양한 Validator를 제공하면 된다.
class LimitDigitValidator : public IValidator
{
    int value;
public:
    LimitDigitValidator(int v) : value(v) {}

    virtual bool validate(string s, char c)
    {
        return s.size() < value && isdigit(c);
    }

    virtual bool is_complete(string s)
    {
        return s.size() == value;
    }
};

int main()
{
    LineEdit edit;
    LimitDigitValidator v(5);

    edit.set_validator(&v);

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