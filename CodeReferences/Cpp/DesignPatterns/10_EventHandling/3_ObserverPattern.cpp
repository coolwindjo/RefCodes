#include <iostream>
using namespace std;

#include <vector>


struct IMenuListener
{
    virtual void on_command(int id) = 0;
    virtual ~IMenuListener() {}
};

class MenuItem
{
    int id;
    //IMenuListener* pListener;
    vector<IMenuListener*> v;

public:
    MenuItem(int i)
        : id(i)
    {}

    void add_listener(IMenuListener* pL)
    {
        v.push_back(pL);
    }

    virtual void command()
    {
        // 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
        // "객체가 외부로 이벤트를 발생한다." 라고 표현
        // => 등록된 모든 객체에게 알려준다. => Observer Pattern
        // id로 분기하는 것에 대한 문제점은 해결되지 않고 있다.
        for (int i = 0; i < v.size(); ++i)
        {
            v[i]->on_command(id);
        }
    }

};

class Window : public IMenuListener
{
public:
    virtual void on_command(int id)
    {
        cout << "Window onCommand" << endl;
    }
private:

};

class Dialog : public IMenuListener
{
public:
    Dialog() {}
    ~Dialog() {}
    virtual void on_command(int id)
    {
        switch (id)
        {
        case 11:
            open();
            break;
        case 12:
            close();
            break;
        default:
            break;
        }
        close();
    }

    void open()
    {
        cout << "Dialog open" << endl;
    }
    void close()
    {
        cout << "Dialog close" << endl;
    }
private:

};


int main()
{
    Dialog dia;
    Window win;

    MenuItem m1(11);
   
    m1.add_listener(&dia);
    m1.command();

    m1.add_listener(&win);
    m1.command();

    system("pause");
    return 0;
}