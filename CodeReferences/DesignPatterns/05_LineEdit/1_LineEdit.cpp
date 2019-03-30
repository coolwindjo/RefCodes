// 중요 예제
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

const int kMaxNum = 10000;
// GUI 도구인 LineEdit를 만들어 봅시다.
class LineEdit
{
    string data;
public:
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

            if (isdigit(c))
            {
                data.push_back(c);
                cout << c;
            }
        }

        cout << endl;
        return data;
    }
};


int main()
{
    LineEdit edit;
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