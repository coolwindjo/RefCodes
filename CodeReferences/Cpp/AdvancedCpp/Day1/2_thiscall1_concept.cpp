#include <iostream>

class Point
{
	int x, y;
public:
// 핵심 1. Mehod 호출시 객체 주소(this)가 포함되어 전달됩니다. - this call
	void set(int a, int b)	// void set(Point* this, int a, int b)
	{						
		x = a;				// this->x = a;
		y = b;				// this->y = b;
	}						
// 핵심 2.static member method는 this가 전달되지 않는다. - this call X
	static void foo(int a)
	{
		// x = a;	// errorL this->x 로 변경되어야 하는데.... this 가 없다.
				// static member function에서는 member attribute 접근 안됨
	}
};

int main()
{
	Point::foo(10);	// 객체 없이 호출
					//push 10
					//call Point::foo

	Point p1, p2;

	p1.set(10, 20); // set(&p1, 10, 20)
					//push 20
					//push 10
					//mov ecx, &p1
					//call Point::set
}
