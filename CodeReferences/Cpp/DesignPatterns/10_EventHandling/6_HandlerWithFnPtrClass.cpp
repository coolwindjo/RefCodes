// 8_�޴��̺�Ʈ6
#include <iostream>
using namespace std;

// �Ѱ谡 �ִ�. argument�� �����ϴ� ��å�� ��ϳ�?
// => function �̶�� Class�� �ִ�. (in C++ 2.0)

struct ICommand
{
    virtual void execute() = 0;
    virtual ~ICommand() {}
};

class FunctionCommand : public ICommand
{
    typedef void(*HANDLER)();
    HANDLER handler;
public:
    FunctionCommand(HANDLER h) : handler(h) {}

    void execute() { handler(); }
};

template <typename T>
class MemberCommand : public ICommand
{
    typedef void(T::*HANDLER)();
    HANDLER handler;
    T* object;
public:
    MemberCommand(HANDLER h, T* o) : handler(h), object(o) {}
    void execute() { (object->*handler)(); }
};

template <typename T>
MemberCommand<T>* cmd(void (T::*f)(), T* o)
{
    return new MemberCommand<T>(f, o);
}

FunctionCommand* cmd(void(*f)())
{
    return new FunctionCommand(f);
}
//---------------------------------------
class MenuItem
{
public:
    MenuItem();
    ~MenuItem();
    void set_handler(ICommand* p)
    {
        pCommand = p;
    }
    void command()
    {
        if (pCommand)
        {
            pCommand->execute();
        }
    }
private:
    ICommand* pCommand;
};

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

class Dialog
{
public:
    void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

int main()
{
    Dialog dlg;

    MenuItem m;
    m.set_handler(cmd(&Dialog::close, &dlg));
    m.command();

    m.set_handler(cmd(&foo));
    m.command();

    system("pause");
    return 0;
}