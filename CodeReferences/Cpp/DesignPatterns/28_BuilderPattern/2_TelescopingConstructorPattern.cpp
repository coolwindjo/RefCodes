// ���翡 ���� ����
// Builder -> ������ ���������� ǥ���� �޶����� ��ü�� ���� �� ���
//  => Object ������ ���

//  => Constructor Parameter�� ���� �� ����ϸ� ����

#include <iostream>
using namespace std;
#include <string>

class UserInfo
{
public:
    // ��� 1. Telescoping Constructor Pattern
    //    : ������ ������ ����
#if 0
    UserInfo(string i, string a)
        : id(i)
        , address(a)
    {}
    UserInfo(string i, string a, int l)
        : id(i)
        , address(a)
    {}
    UserInfo(string i, string a, int l, int g)
        : id(i)
        , address(a)
        , level(l)
    {}
    UserInfo(string i, string a, int l, int g, int c)
        : id(i)
        , address(a)
        , level(l)
        , cash(c)
    {}

    UserInfo(string i, string a, int l, int g)
    {
        // this(i, a, l, g, 0); - ������ ���� ��� in java
    }
#endif
    UserInfo(string i, string a)
        : UserInfo(i, a, 0, 0, 0) {}
    UserInfo(string i, string a, int l)
        : UserInfo(i, a, l, 0, 0) {}
    UserInfo(string i, string a, int l, int g)
        : UserInfo(i, a, l, g, 0) // C++11 Delegating Constructor
    {}

    UserInfo(string i, string a, int l, int g, int c)
        : id(i), address(a), level(l), gold(g), cash(c) {}

    ~UserInfo() {}

private:
    const string id;        // �ʼ� ����
    const string address;
   
    int level;              // ���� ����
    int gold;
    int cash;
};

int main()
{
    UserInfo ui("i","a");
    // �� ������� ��ü�� ������ ���� �����Ϸ��� ���� ������ �´�
    // �����ڸ� �����ؼ� �����ϸ� �ȴ�.
    UserInfo ui("chansik.yun", "����", 0, 1000, 100000);
        // ������ 
        //   1) �������� ���� �ʴ�. � ���ڰ� � ����� �ʱ�ȭ�ϴ���
        //      �˱� ��ƴ�.
        //   2) ���� Ÿ���� ���ڿ� ���ؼ� ������ �ٲ� ��� ������ ������
        //      �߻����� �ʽ��ϴ�.

    system("pause");
    return 0;
}