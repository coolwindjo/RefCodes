// 1_�湮��
// �����̳�(���� ��ü)�� �ۿ��ϴ� ���� 2����
// �ݺ���: �����̳ʳ� ���� ��ü�� ���� ������ ������� ��Ҹ� ����
// �湮��: �����̳ʿ� ���� ��ü�� ���� ������ ������� ��ҿ� ����

#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// Composit Pattern
// : ���� ��ü�� �����ϴ� ��� - menu, folder: Composite Pattern
// 1. ���հ�ü (Popup Menu)�� ������ü(MenuItem)�� ���հ�ü�� ��� ������ �� �ִ�.
//  => ���հ�ü�� ���� ��ü���� ������ �θ� �����Ѵ�.
// 2. ���հ�ü�� ������ü�� ���Ͻ�(������  ����.=> ��� command()�� �ִ�.)�ȴ�. 

// - �湮�� ������ Composite ���ϰ� ����Ǿ ���� ���˴ϴ�.

// ���� ����
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


// ��� �޴��� ������ �θ�
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
    // �ݵ�� command()�� �θ��� BaseMenu�κ��� �;��Ѵ�.
    // �θ� ���忡���� �������� ������ ����, �ڽ��� �ݵ�� �������Ѵٸ�, 
    // ���� ���� �Լ��� ����.
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

// �Ʒ� Class�� �ٽ��Դϴ�.
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

        // ���� �����ϰ� �ִ� ��� �޴��鿡 ���ؼ��� �湮�ڸ� �����ؾ� �Ѵ�. - �ٽ�!!!
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
            cout << sz + 1 << ". ���� �޴���" << endl;

            cout << "Choose a menu >> ";
            int cmd;
            cin >> cmd;

            if (cmd == sz + 1)
                break;

            if (cmd < 1 || cmd > sz + 1)  // �߸��� �Է�
                continue;

            // ���õ� �޴��� �����Ѵ�.
            v[cmd - 1]->command();
        }


    }
private:
    //string title;
    vector<BaseMenu*> v;    // ����� �ռ�
};

PopupMenu::~PopupMenu()
{
}



//--------------------------------------
// �޴� �ý��ۿ� �پ��� ����� �߰��ϴ� �湮�ڵ��� �����ϸ� �˴ϴ�.
class TitleDecorationVisitor : public IMenuVisitor
{
public:
    virtual void visit(MenuItem* p) {}
    virtual void visit(PopupMenu* p)
    {
        string s = p->get_title();
        s = s + "  >";
        p->set_title(s);  // ĸ��ȭ ���� ����
                         // ������ �����ߴ� ��å�� �ٲ�� �Ѵ�.
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