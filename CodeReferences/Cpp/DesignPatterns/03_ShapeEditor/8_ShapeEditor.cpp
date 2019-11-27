#include <iostream>
#include <vector>

using namespace std;

// 
// 1. ��� Shape�� Typeȭ(Classȭ) �ϸ� ���ϴ�.
// 2. ��� Shape�� Common Parent�� �ִٸ�, ��� Shape�� ��� ���� �� �� �ִ�.
// 3. ��� Children�� Common Feature�� �ִٸ�, �ݵ�� Parent���� �־�� �Ѵ�.
//      �׷��� Parent Pointer�� ��� ����� �� �ش� Feature�� �̿��� �� �ִ�. - LSP
// 4. Parent�� Function �� �ڽ��� ������ �ϴ� ��� �Լ��� �ݵ�� Virtual Function �̾�� �Ѵ�.
//      "�����Լ��� �ƴ� �Լ��� ������ ���� ����" - Effective C++
// 5. ����� �߰��Ǿ                 (��� Ȯ�忡 �� Open�Ǿ� �ְ�,)
//      ���� �ڵ�� �����Ǹ� �ȵȴ�.    (�ڵ� �������� Close�Ǿ�� �Ѵ�.)
//      �Ѵٴ� �̷� => OCP (Open Close Principal)
// 6. Polymorphism�� OCP�� �����Ѵ�.
// 7. Prototype Pattern: ������ Object�� �����ؼ� ���ο� Object�� ����� ����
//                      - "Polymorphism"�� �̿��� Object�� ����
// java: Cloneable      C#: ICloneable
// java: clone();       C#: Clone();
// ObjC: Copyable();    copy();
// 8. "Replace type code with polymorphism"
//      => Refactoring term.
// ���� �����ڸ� �̿��ϴ� ���� ������ �� �ִ�. - Effective java
// 9. Template Method Pattern : ������ �ʴ� ��ü �˰����� �θ� �� �����Լ��� ����
//                              ���ؾ� �ϴ� �κ��� �����Լ�ȭ �ؼ�
//                              Child Class�� ������ �� �ְ� ������ �ϴ� ���
//                              => NVI(Non Virtual Interface)
// 10. DRY (Do not Repeat Yourself) : �ڵ��� �ߺ��� �ڵ��� �������� ����� ���� ��Ų��.
//      ThisCall 4���� �����Ͽ� ����

class Shape
{
public:
    // ������ �ʴ� ��ü �帧���� ���ؾ� �ϴ� �κ��� ã�Ƽ� 
    // �����Լ��� �и��ؾ� �Ѵ�.
    // "���뼺�� �������� �и� ���"

    // in Java: final method - over riding ����
    void draw() //  ���� �κ�
    {
        cout << "mutex lock" << endl;

        draw_impl();

        cout << "mutex unlock" << endl;
    }

    virtual void draw_impl()    // ���� �κ�
    {
        cout << "Shape Draw" << endl;
    }

    // �ڽ��� ���纻�� ����� �����Լ��� ������ ����.
    virtual Shape* clone()
    {
        return new Shape(*this);
    }
};

class Rect : public Shape
{
public:
    void draw_impl()
    {
        cout << "Rect draw" << endl;
    }
    virtual Rect* clone()
    {
        return new Rect(*this);
    }
};

class Circle : public Shape
{
public:
    void draw_impl()
    {
        cout << "Circle draw" << endl;
    }
    virtual Circle* clone()
    {
        return new Circle(*this);
    }
};

const int kMaxNum = 1000;
int main()
{
    vector<Shape*> v;

    for (int i = 0; 
    true 
        && (i < kMaxNum); i++)
    {
        int cmd;

        cin >> cmd;

        if (cmd == 1)
        {
            v.push_back(new Rect);
        }
        else if (cmd == 2)
        {
            v.push_back(new Circle);
        }
        else if (cmd == 8)
        {
            cout << "Which polygon do you want to duplicate? >> " << endl;
            int k;
            cin >> k;

            // v[k] - Rect? Circle?
            v.push_back(v[k]->clone());
        }
        else if (cmd == 9)
        {
            for (int j = 0; j < static_cast<int>(v.size()); j++)
            {
                v[j]->draw();
            }
        }
    }

    system("pause");
    return 0;
}