// 3 page ~
#include <iostream>
// 핵심 1. 멤버 함수 호출시 객체 주소(this)가 포함해서 전달됩니다. - this call
//      2. static 멤버 함수는 this가 전달되지 않습니다. - this call 이 아님.
class Point
{
	int x, y;
public:
	void set(int a, int b) // void set(Point* this, int a, int b)
	{						
		x = a;			  // 	this->x = a
		y = b;			  //	this->y = b;
	}						
	static void foo(int a)// void foo(int a)
	{
		x = a;		// this->x 로 변경되어야 하는데..this가 없다.
	}				// 그래서 error.
					// static 멤버 함수에서는 멤버 변수 접근 안됨.
};
int main()
{
	Point::foo(10); // 객체 없이 호출..
					// push 10
					// call Point::foo

	Point p1, p2;

	p1.set(10, 20); // set(&p1, 10, 20) 
				// push	20
				// push 10	진짜 인자는 스택으로
				// mov  ecx, &p1
				// call Point::set  
}



