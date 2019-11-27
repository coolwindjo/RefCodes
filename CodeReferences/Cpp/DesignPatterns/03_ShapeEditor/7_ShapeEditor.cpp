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


class Shape
{
public:
    virtual void draw()
    {
        cout << "Shape Draw" << endl;
    }
};

class Rect : public Shape
{
public:
    void draw()
    {
        cout << "Rect draw" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "Circle draw" << endl;
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
        else if (cmd == 9)
        {
            for (int j = 0; j < v.size(); j++)
            {
                v[j]->draw();
            }
        }
    }

    system("pause");
    return 0;
}