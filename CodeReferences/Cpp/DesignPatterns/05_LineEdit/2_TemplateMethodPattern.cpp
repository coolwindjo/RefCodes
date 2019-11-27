// �߿� ����
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

// �Ѱ���
//  1) ����ð��� ��å�� ��ü�ϴ� ���� �Ұ����ϴ�.
//      ��ü�� ������ �ƴ� Ŭ������ ����
//  2) ���ο��� ���Ǵ� ��å�� �ٸ� Ŭ�������� �����ϴ� ���� �Ұ����ϴ�.

const int kMaxNum = 10000;
// GUI ������ LineEdit�� ����� ���ô�.
class LineEdit
{
    string data;
public:
    // Validation ��å�� ������ �����ؾ� �Ѵ�.
    //  - ������ �ʴ� �ڵ�(���뼺)���� ���ؾ� �ϴ� �� (������)�� �ִٸ�,
    //  �и��ؾ��Ѵ�.

    // ��� 1. ���ϴ� ���� virtual function���� �����. = "Template method pattern"
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

// ���� ��å�� �����ϰ� �ʹٸ� �Ļ� Ŭ�������� �����Լ��� �������ϸ� �ȴ�.
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