// �߿� ����
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

// ���뼺�� �������� �и��ϴ� 
// ��� 2. ���ϴ� ���� Interface based Class�� �и��Ѵ�. (Strategy Pattern)
// ����
//  1) ����ð��� ��å�� ��ü�ϴ� ���� �����ϴ�.
//  2) ���ο��� ���Ǵ� ��å�� �ٸ� Ŭ�������� �����ϴ� ���� �����ϴ�.

// Qt��� ���� �ҽ� GUI ���̺귯������ QValidator��� Interface�� �ֽ��ϴ�.

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

// GUI ������ LineEdit�� ����� ���ô�.
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

// ���� �پ��� Validator�� �����ϸ� �ȴ�.
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