#include<iostream>

using namespace std;

class Point
{
    int x, y;
public:
    void set(int a, int b)  // void set(Point* const this, int a, int b)
    {
        x = a;              // this->x = a;
        y = b;              // this->y = b;
    }

    static void foo(int a)  // void foo(int a)
    {
        //x = a;      // this->x�� �Ǿ�� �ϴµ�, this�� ����.
    }
};

int main()
{
    Point::foo(10); // ���� ��� �Լ��� ��ü ���� ȣ�Ⱑ�� �ϴ�.
    Point p1, p2;
    p1.set(10, 20); // compiled as "set(&p1, 10, 20)"
                    // push 20
                    // push 10
                    // mov ecx, &p1
                    // call set
    
}