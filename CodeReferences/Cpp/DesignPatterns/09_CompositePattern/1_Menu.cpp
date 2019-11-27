#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// Composit Pattern
// : 복합객체를 구성하는 방법
// 1. 복합객체 (Popup Menu)는 개별개체(MenuItem)과 복합객체를 모두 보관할 수 있다.
//  => 복합객체와 단일 객체간의 공통의 부모가 존재한다.
// 2. 복합객체와 개별객체가 동일시(사용법이  같다.=> 모두 command()가 있다.)된다. 

// 모든 메뉴의 공통의 부모
class BaseMenu
{
public:
    BaseMenu(string s);
    virtual ~BaseMenu() {}
    string get_title()
    {
        return title;
    }
    virtual void command() = 0;
    // 반드시 command()는 부모인 BaseMenu로부터 와야한다.
    // 부모 입장에서는 구현해줄 내용이 없고, 자식이 반드시 만들어야한다면, 
    // 순수 가상 함수가 좋다.
private:
    string title;

};

BaseMenu::BaseMenu(string s)
    : title(s)
{
}


class MenuItem : public BaseMenu
{
public:
    MenuItem(string s);
    ~MenuItem();
    void command()
    {
        cout << get_title() << "Menu has been selected." << endl;
    }
private:
    //string title;
};

MenuItem::MenuItem(string s)
    //: title(s)
    : BaseMenu(s)
{

}

MenuItem::~MenuItem()
{
}


#define clrscr() system("cls")      // system("clear")

// 아래 Class가 핵심입니다.
class PopupMenu : public BaseMenu
{
public:
    PopupMenu(string s);
    ~PopupMenu();


    void add_menu(BaseMenu* p) { v.push_back(p); }

    void command()
    {

        while (1)
        {
            clrscr();

            int sz = v.size();
            for (int i = 0; i < sz; i++)
                cout << i + 1 << ". " << v[i]->get_title() << endl;
            cout << sz + 1 << ". 상위 메뉴로" << endl;

            cout << "Choose a menu >> ";
            int cmd;
            cin >> cmd;
            
            if (cmd == sz + 1)
                break;

            if (cmd < 1 || cmd > sz + 1)  // 잘못된 입력
                continue;

            // 선택된 메뉴를 실행한다.
            v[cmd - 1]->command();
        }


    }
private:
    //string title;
    vector<BaseMenu*> v;    // 재귀적 합성
};

PopupMenu::PopupMenu(string s)
    //: title(s)
    : BaseMenu(s)
{
}

PopupMenu::~PopupMenu()
{
}


int main()
{
    PopupMenu* menubar = new PopupMenu("MenuBar");
    PopupMenu* p1 = new PopupMenu("Display setting");
    PopupMenu* p2 = new PopupMenu("Sound setting");

    menubar->add_menu(p1);
    menubar->add_menu(p2);

    p1->add_menu(new MenuItem("Resolution setting"));
    p1->add_menu(new MenuItem("Color setting"));
    p1->add_menu(new MenuItem("Etc. setting"));

    p2->add_menu(new MenuItem("Volume setting"));
    p2->add_menu(new MenuItem("Sound color setting"));

    menubar->command();

    system("pause");
    return 0;
}