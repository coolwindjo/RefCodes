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
// 5. 기능이 추가되어도                 (기능 확장에 는 Open되어 있고,)
//      기존 코드는 수정되면 안된다.    (코드 수정에는 Close되어야 한다.)
//      한다는 이론 => OCP (Open Close Principal)
// 6. Polymorphism은 OCP를 만족한다.
// 7. Prototype Pattern: 기존의 Object를 복사해서 새로운 Object를 만드는 패턴
//                      - "Polymorphism"을 이용한 Object의 복사
// java: Cloneable      C#: ICloneable
// java: clone();       C#: Clone();
// ObjC: Copyable();    copy();
// 8. "Replace type code with polymorphism"
//      => Refactoring term.
// 복사 생성자를 이용하는 것이 안전할 수 있다. - Effective java
// 9. Template Method Pattern : 변하지 않는 전체 알고리즘은 부모가 비 가상함수로 제공
//                              변해야 하는 부분은 가상함수화 해서
//                              Child Class가 변경할 수 있게 디자인 하는 방법
//                              => NVI(Non Virtual Interface)
// 10. DRY (Do not Repeat Yourself) : 코드의 중복은 코드의 유지보수 비용을 증가 시킨다.
//      ThisCall 4번과 연계하여 공부

class Shape
{
public:
    // 변하지 않는 전체 흐름에서 변해야 하는 부분을 찾아서 
    // 가상함수로 분리해야 한다.
    // "공통성과 가변성의 분리 방법"

    // in Java: final method - over riding 금지
    void draw() //  공통 부분
    {
        cout << "mutex lock" << endl;

        draw_impl();

        cout << "mutex unlock" << endl;
    }

    virtual void draw_impl()    // 가변 부분
    {
        cout << "Shape Draw" << endl;
    }

    // 자신의 복사본을 만드는 가상함수가 있으면 좋다.
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