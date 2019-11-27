#include <iostream>
using namespace std;

#include <string>
#include <conio.h>  // getch();
#include <vector>

// 7_Composite

// 파일은 자신의 크기가 있지만, 폴더는 자신의 크기가 없습니다.
// 하지만 파일과 폴더 모두 크기를 구할 수 있습니다.

// 1. File과 Folder의 공통의 부모 : Item
// 2. File과 Folder의 사용법 : get_size()
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

// C++ 에서는 Composite Pattern을 구현할 때, 포함하고 있는 모든 객체에 대한 
// 메모리 해지에 책임이 있다.
Folder::~Folder()
{
    for (int i = 0; i < v.size(); ++i)
    {
        delete v[i];
    }
}

int main()
{
    // 아래코드가 실행되도록 Folder, File 클래스를 만들어 보세요
    Folder* fol1 = new Folder("ROOT");
    Folder* fol2 = new Folder("A");

    File* f1 = new File("a.txt", 10); // 이름, 크기
    File* f2 = new File("b.txt", 20);

    // 관계설정
    fol2->add_item(f1);
    fol1->add_item(f2);
    fol1->add_item(fol2);
    // fol1 - fol2 - f1
    //      - f2
    cout << f2->get_size() << endl; // 20
    cout << fol2->get_size() << endl; // 10
    cout << fol1->get_size() << endl; // 30

    // 문제되는 것
    /*
    Folder f3("...");
    fol1->add_item(&f3);
    */ // 반드시 힙에다가 생성하도록 약속해야 함

    delete fol1;

    system("pause");
    return 0;
}