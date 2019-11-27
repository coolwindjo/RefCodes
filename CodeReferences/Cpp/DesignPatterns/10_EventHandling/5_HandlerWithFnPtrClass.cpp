#include <iostream>
using namespace std;
// 일반 함수와 모든 클래스의 멤버 함수를 보관하는 범용적 함수 포인터 타입을 만들어 보자.

// 3. A와 B를 묶기 위해서는 공통의 부모를 제공해야 한다.
//  => FunctionCommand와 MemberCommand의 공통의 부모를 설계하자
struct ICommand
{
    virtual void execute() = 0;
    virtual ~ICommand() {}
};

// 1. Function Pointer 개념을 Class로 Wrapping 해봅시다.
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

// 2. 모든 클래스의 멤버함수의 주소를 담을 수 있는 클래스를 설계해보자.
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

// 4. 클래스 템플릿은 암시적 추론이 불가능하기 때문에 항상 복잡해 보입니다.
//    암시적 추론이 가능한 함수 템플릿으로 헬퍼를 제공합니다.
template <typename T>
MemberCommand<T>* cmd(void (T::*f)(), T* o)
{
    return new MemberCommand<T>(f, o);
}

// 5. 라이브러리 일관성을 위해서 FunctionCommand를 만드는 cmd도 제공합니다.
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