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
        // �޴��� ���õ� ����� �ٽ� �ܺο� �˷��� �Ѵ�.
        // "��ü�� �ܺη� �̺�Ʈ�� �߻��Ѵ�." ��� ǥ��
        // => ��ϵ� ��� ��ü���� �˷��ش�. => Observer Pattern
        // id�� �б��ϴ� �Ϳ� ���� �������� �ذ���� �ʰ� �ִ�.
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