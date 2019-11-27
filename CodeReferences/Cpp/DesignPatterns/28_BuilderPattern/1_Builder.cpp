#include <iostream>
#include <string>
using namespace std;

struct IBuilder
{
    virtual void makeHat() = 0;
    virtual void makeUniform() = 0;
    virtual void makeShoes() = 0;

    virtual string getResult() = 0;

    virtual ~IBuilder() {}
};

class Director
{
    IBuilder* pBuilder;
public:
    void setBuilder(IBuilder* p) { pBuilder = p; }

    // �Ʒ� �Լ��� ĳ���͸� ���� �����ϴ� �Լ��Դϴ�.
    string construct()
    {
        pBuilder->makeHat();
        pBuilder->makeShoes();
        pBuilder->makeUniform();

        return pBuilder->getResult();
    }
};

// �پ��� ������ Builder�� �����մϴ�.
class Korean : public IBuilder
{
public:
    Korean(){}
    ~Korean(){}

    virtual void makeHat()
    {
        c += "��";
    }
    virtual void makeUniform()
    {
        c += "�Ѻ�";
    }
    virtual void makeShoes()
    {
        c += "����";
    }

    virtual string getResult() { return c; }
private:
    string c;
};

class American : public IBuilder
{
public:
    American() {}
    ~American() {}

    virtual void makeHat()
    {
        c += "�߱�����";
    }
    virtual void makeUniform()
    {
        c += "�纹";
    }
    virtual void makeShoes()
    {
        c += "����";
    }

    virtual string getResult() { return c; }
private:
    string c;
};

int main()
{
    Korean korean; American american;
    Director director;

    // ĳ���� ���� ȭ��ǥ Ű�� ������ �� �ڵ带 �����Ѵ�.
    director.setBuilder(&korean);
    cout << director.construct() << endl;

    director.setBuilder(&american);
    cout << director.construct() << endl;

    system("pause");
    return 0;
}