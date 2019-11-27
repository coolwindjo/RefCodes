#include <iostream>
using namespace std;
// �Ϲ� �Լ��� ��� Ŭ������ ��� �Լ��� �����ϴ� ������ �Լ� ������ Ÿ���� ����� ����.

// 3. A�� B�� ���� ���ؼ��� ������ �θ� �����ؾ� �Ѵ�.
//  => FunctionCommand�� MemberCommand�� ������ �θ� ��������
struct ICommand
{
    virtual void execute() = 0;
    virtual ~ICommand() {}
};

// 1. Function Pointer ������ Class�� Wrapping �غ��ô�.
class FunctionCommand : public ICommand
{
    typedef void(*HANDLER)();

public:
    FunctionCommand(HANDLER h);
    ~FunctionCommand();

    void execute()
    {
        handler();
    }
private:
    HANDLER handler;
};

FunctionCommand::FunctionCommand(HANDLER h)
    : handler(h)
{
}

FunctionCommand::~FunctionCommand()
{
}

// 2. ��� Ŭ������ ����Լ��� �ּҸ� ���� �� �ִ� Ŭ������ �����غ���.
template <typename T>
class MemberCommand : public ICommand
{
    typedef void(T::*HANDLER)();

public:
    MemberCommand(HANDLER h, T* o)
        : handler(h)
        , object(o)
    {
    }

    ~MemberCommand(){}

    void execute()
    {
        (object->*handler)();
    }
private:
    HANDLER handler;
    T* object;
};


class Dialog
{
public:
    Dialog();
    ~Dialog();
    void close()
    {
        cout << "Dialog close" << endl;
    }
private:

};

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}

void foo()
{
    cout << "foo" << endl;
}

// 4. Ŭ���� ���ø��� �Ͻ��� �߷��� �Ұ����ϱ� ������ �׻� ������ ���Դϴ�.
//    �Ͻ��� �߷��� ������ �Լ� ���ø����� ���۸� �����մϴ�.
template <typename T>
MemberCommand<T>* cmd(void (T::*f)(), T* o)
{
    return new MemberCommand<T>(f, o);
}

// 5. ���̺귯�� �ϰ����� ���ؼ� FunctionCommand�� ����� cmd�� �����մϴ�.
FunctionCommand* cmd(void(*f)())
{
    return new FunctionCommand(f);
}

int main()
{
    // ICommand* p = new FunctionCommand(&foo);
    ICommand* p = cmd(&foo);
    p->execute();

    Dialog dlg;
    //p = new MemberCommand<Dialog>(&Dialog::close, &dlg);
    p = cmd(&Dialog::close, &dlg);
    p->execute();

    system("pause");
    return 0;
}

#if 0
int main()
{
    Dialog dlg;
    MemberCommand<Dialog> mc(&Dialog::close, &dlg);
    mc.execute();

    FunctionCommand fc(&foo);
    fc.execute();

    system("pause");
    return 0;
}
#endif