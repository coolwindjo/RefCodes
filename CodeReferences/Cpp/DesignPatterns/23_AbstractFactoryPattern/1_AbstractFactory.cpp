// Abatract Factory

// 의도: 공장도 인터페이스 기반으로 설계해서
//       교체가능하게 하자.

// Style~~
// Qt에서 제공하는 GUI Look & Feel의 원리를 살펴봅시다.
#include <iostream>
using namespace std;

struct IButton
{

};
class XPButton : public IButton {};
class GTKButton : public IButton {};

struct IEdit
{

};
class XPEdit : public IEdit {};
class GTKEdit : public IEdit {};


struct IFactory
{
    virtual IButton* create_button() = 0;
    virtual IEdit* create_edit() = 0;

    virtual ~IFactory() {}
};


// 스타일에 따라 컨트롤을 만드는 공장을 도입하자.
class XPFactory
{
public:
    IButton* create_button() { return new XPButton; }
    IEdit* create_edit() { return new XPEdit; }
    // ...
};

class GTKFactory
{
public:
    IButton* create_button() { return new GTKButton; }
    IEdit* create_edit() { return new GTKEdit; }
    // ...
};

// a.exe --style=XP  or --style=GTK
int main(int argc, char* argv[])
{
    IButton* p1;
    IEdit* p2;

#if _DEBUG
    char* arg1 = "--style=GTK";
    argv[1] = arg1;
#endif
    if (strcmp(argv[1], "--style=GTK") == 0)
    {
        p1 = new GTKButton;
        p2 = new GTKEdit;
        // ...
    }
    else
    {
        p1 = new XPButton;
        p2 = new XPEdit;
        // ...
    }

    // Window를 그리는 코드에서 
    //p1->draw();
    //p2->draw();

    system("pause");
    return 0;
}