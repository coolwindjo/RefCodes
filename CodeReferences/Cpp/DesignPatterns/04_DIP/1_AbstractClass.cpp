#include <iostream>
using namespace std;

// Abatract Class��?
// : Pure virtual function�� 1�� �̻� �ִ� Class
// : Derived class���� Ư�� function�� �ݵ�� ������ �����ϴ� ��

class Polygon
{
public:
    virtual void draw() = 0;        // Pure virtual function.
};

class Rect : public Polygon     // draw()�� �����θ� �������� ������ 
                                // ���� �߻� Ŭ������.
{
    virtual void draw()
    {
        return ; 
    } 
};

int main()
{
    //Polygon p;
    Rect r;


    system("pause");
    return 0;
}