#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// 7_Composite

// ������ �ڽ��� ũ�Ⱑ ������, ������ �ڽ��� ũ�Ⱑ �����ϴ�.
// ������ ���ϰ� ���� ��� ũ�⸦ ���� �� �ֽ��ϴ�.

// 1. File�� Folder�� ������ �θ� : Item
// 2. File�� Folder�� ���� : get_size()
class Item
{
public:
    Item(string s);
    virtual ~Item() {}
    virtual int get_size() = 0;     // Pure virtual function
    string get_name()
    {
        return name;
    }
private:
    string name;
};

Item::Item(string s)
    : name (s)
{
}


class File  : public Item
{
public:
    File(string n, int s);
    ~File();
    virtual int get_size() 
    {
        return size;
    }

private:
    int size;
};

File::File(string n, int s)
    : Item(n)
    , size(s)
{
}

File::~File()
{
}


class Folder : public Item
{
public:
    Folder(string s);
    ~Folder();

    void add_item(Item* it)
    {
        v.push_back(it);
    }

    virtual int get_size()
    {
        int sum = 0;
        for (int i = 0; i < v.size(); ++i)
        {
            sum += v[i]->get_size();
        }
        return sum;
    }
private:
    vector<Item*> v;
};

Folder::Folder(string s)
    : Item(s)
{
}

// C++ ������ Composite Pattern�� ������ ��, �����ϰ� �ִ� ��� ��ü�� ���� 
// �޸� ������ å���� �ִ�.
Folder::~Folder()
{
    for (int i = 0; i < v.size(); ++i)
    {
        delete v[i];
    }
}

int main()
{
    // �Ʒ��ڵ尡 ����ǵ��� Folder, File Ŭ������ ����� ������
    Folder* fol1 = new Folder("ROOT");
    Folder* fol2 = new Folder("A");

    File* f1 = new File("a.txt", 10); // �̸�, ũ��
    File* f2 = new File("b.txt", 20);

    // ���輳��
    fol2->add_item(f1);
    fol1->add_item(f2);
    fol1->add_item(fol2);
    // fol1 - fol2 - f1
    //      - f2
    cout << f2->get_size() << endl; // 20
    cout << fol2->get_size() << endl; // 10
    cout << fol1->get_size() << endl; // 30

    // �����Ǵ� ��
    /*
    Folder f3("...");
    fol1->add_item(&f3);
    */ // �ݵ�� �����ٰ� �����ϵ��� ����ؾ� ��

    delete fol1;

    system("pause");
    return 0;
}