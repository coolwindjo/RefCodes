#include <iostream>
using namespace std;

// 1. interface based listener concept: java, Android
// Menu를 처리하고 싶은 모든 클래스는 아래 interface를 구현해야 한다.
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
        // 메뉴가 선택된 사실을 다시 외부에 알려야 한다.
        // "객체가 외부로 이벤트를 발생한다." 라고 표현
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