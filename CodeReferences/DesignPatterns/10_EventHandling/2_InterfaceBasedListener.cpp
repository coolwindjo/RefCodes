#include <iostream>
using namespace std;

// 1. interface based listener concept: java, Android
// Menu�� ó���ϰ� ���� ��� Ŭ������ �Ʒ� interface�� �����ؾ� �Ѵ�.
struct IMenuListener
{
    virtual void on_command(int id) = 0;
    virtual ~IMenuListener() {}
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

class MenuItem
{
    int id;
    IMenuListener* pListener;
public:
    MenuItem(int i)
        : pListener(0)
        , id(i)
    {}

    void set_listener(IMenuListener* pL)
    {
        pListener = pL;
    }

    virtual void command()
    {
        // �޴��� ���õ� ����� �ٽ� �ܺο� �˷��� �Ѵ�.
        // "��ü�� �ܺη� �̺�Ʈ�� �߻��Ѵ�." ��� ǥ��
        if (pListener)
        {
            pListener->on_command(id);
        }
    }

};

int main()
{
    Dialog dia;

    MenuItem m1(11); MenuItem m2(12);

    m1.set_listener(&dia);
    m2.set_listener(&dia);

    m1.command();
    m2.command();

    system("pause");
    return 0;
}