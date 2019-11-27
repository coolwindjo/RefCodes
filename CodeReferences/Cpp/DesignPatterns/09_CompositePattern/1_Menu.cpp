#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// Composit Pattern
// : ���հ�ü�� �����ϴ� ���
// 1. ���հ�ü (Popup Menu)�� ������ü(MenuItem)�� ���հ�ü�� ��� ������ �� �ִ�.
//  => ���հ�ü�� ���� ��ü���� ������ �θ� �����Ѵ�.
// 2. ���հ�ü�� ������ü�� ���Ͻ�(������  ����.=> ��� command()�� �ִ�.)�ȴ�. 

// ��� �޴��� ������ �θ�
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
    // �ݵ�� command()�� �θ��� BaseMenu�κ��� �;��Ѵ�.
    // �θ� ���忡���� �������� ������ ����, �ڽ��� �ݵ�� �������Ѵٸ�, 
    // ���� ���� �Լ��� ����.
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

// �Ʒ� Class�� �ٽ��Դϴ�.
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