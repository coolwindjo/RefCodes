// 1_방문자
// 컨테이너(복합 객체)에 작용하는 패턴 2가지
// 반복자: 컨테이너나 복합 객체의 내부 구조에 상관없이 요소를 열거
// 방문자: 컨테이너와 복합 객체의 내부 구조에 상관없이 요소에 연산

#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// Composit Pattern
// : 복합 객체를 구성하는 방법 - menu, folder: Composite Pattern
// 1. 복합객체 (Popup Menu)는 개별개체(MenuItem)과 복합객체를 모두 보관할 수 있다.
//  => 복합객체와 단일 객체간의 공통의 부모가 존재한다.
// 2. 복합객체와 개별객체가 동일시(사용법이  같다.=> 모두 command()가 있다.)된다. 

// - 방문자 패턴은 Composite 패턴과 연계되어서 많이 사용됩니다.

// 전방 선언
class PopupMenu;
class MenuItem;

struct IMenuVisitor
{
    virtual void visit(PopupMenu* p) = 0;
    virtual void visit(MenuItem* p) = 0;
    virtual ~IMenuVisitor(void) {}
};

struct IMenuAcceptor
{
    virtual void accept(IMenuVisitor* pVisitor) = 0;
    virtual ~IMenuAcceptor(void) {}
};


// 모든 메뉴의 공통의 부모
class BaseMenu : public IMenuAcceptor
{
public:
    BaseMenu(string s)
    : title(s)
    {
    }
    virtual ~BaseMenu() {}
    string get_title() { return title; }

    //---------
    void set_title(const string& s) { title = s; }
    //---------

    virtual void command() = 0;
    // 반드시 command()는 부모인 BaseMenu로부터 와야한다.
    // 부모 입장에서는 구현해줄 내용이 없고, 자식이 반드시 만들어야한다면, 
    // 순수 가상 함수가 좋다.
private:
    string title;

};

class MenuItem : public BaseMenu
{
public:
    MenuItem(string s)
    //: title(s)
    : BaseMenu(s)
    {}
    ~MenuItem();

    void accept(IMenuVisitor* pVisitor)
    {
        pVisitor->visit(this);
    }

    void command()
    {
        cout << get_title() << "Menu has been selected." << endl;
        getch();
    }
private:
    //string title;
};

MenuItem::~MenuItem()
{
}


#define clrscr() system("cls")      // system("clear")

// 아래 Class가 핵심입니다.
class PopupMenu : public BaseMenu
{
public:
    PopupMenu(string s)
    //: title(s)
    : BaseMenu(s)
    {
    }
    ~PopupMenu();

    virtual void accept(IMenuVisitor* pVisitor)
    {
        pVisitor->visit(this);

        // 내가 포함하고 있는 모든 메뉴들에 대해서도 방문자를 전달해야 한다. - 핵심!!!
        for (BaseMenu* e : v) // Range-for
            e->accept(pVisitor);
    }

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

PopupMenu::~PopupMenu()
{
}



//--------------------------------------
// 메뉴 시스템에 다양한 기능을 추가하는 방문자들을 제공하면 됩니다.
class TitleDecorationVisitor : public IMenuVisitor
{
public:
    virtual void visit(MenuItem* p) {}
    virtual void visit(PopupMenu* p)
    {
        string s = p->get_title();
        s = s + "  >";
        p->set_title(s);  // 캡슐화 전략 위배
                         // 기존에 설계했던 정책을 바꿔야 한다.
    }
};



int main()
{
    PopupMenu* menubar = new PopupMenu("MenuBar");
    PopupMenu* p1 = new PopupMenu("Display setting");
    PopupMenu* p2 = new PopupMenu("Sound setting");

    menubar->add_menu(p1);
    p1->add_menu(p2);
    //menubar->add_menu(p2);

    p1->add_menu(new MenuItem("Resolution setting"));
    p1->add_menu(new MenuItem("Color setting"));
    p1->add_menu(new MenuItem("Etc. setting"));

    p2->add_menu(new MenuItem("Volume setting"));
    p2->add_menu(new MenuItem("Sound color setting"));

    TitleDecorationVisitor v;
    menubar->accept(&v);
    menubar->command();

    system("pause");
    return 0;
}