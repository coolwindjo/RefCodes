// Abatract Factory

// �ǵ�: ���嵵 �������̽� ������� �����ؼ�
//       ��ü�����ϰ� ����.

// Style~~
// Qt���� �����ϴ� GUI Look & Feel�� ������ ���캾�ô�.
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


// ��Ÿ�Ͽ� ���� ��Ʈ���� ����� ������ ��������.
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

    // Window�� �׸��� �ڵ忡�� 
    //p1->draw();
    //p2->draw();

    system("pause");
    return 0;
}