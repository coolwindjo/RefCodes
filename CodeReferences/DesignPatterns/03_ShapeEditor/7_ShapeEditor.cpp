#include <iostream>
#include <vector>

using namespace std;

// 
// 1. 모든 Shape을 Type화(Class화) 하면 편리하다.
// 2. 모든 Shape의 Common Parent가 있다면, 모든 Shape을 묶어서 관리 할 수 있다.
// 3. 모든 Children의 Common Feature가 있다면, 반드시 Parent에도 있어야 한다.
//      그래야 Parent Pointer로 묶어서 사용할 때 해당 Feature를 이용할 수 있다. - LSP
// 4. Parent의 Function 중 자식이 재정의 하는 모든 함수는 반드시 Virtual Function 이어야 한다.
//      "가상함수가 아닌 함수는 재정의 하지 말라" - Effective C++


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