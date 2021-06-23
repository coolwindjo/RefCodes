
#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};
int main()
{
	Point pt(1, 2);
	
	pt.x = 10;			// ok
//	Point(1, 2).x = 10;	// error. 임시객체는 등호의 왼쪽에 놓을수 없다.				
//	Point(1, 2).set(10, 20); // ok.. 즉, 임시객체가 상수는 아닙니다.

	Point* p1 = &pt;			// ok
//	Point* p2 = &Point(1, 2);	// error. 임시객체는 주소연산자로 주소를 구할수 없다.						

	Point& r1 = pt;			 // ok
//	Point& r2 = Point(1, 2); // error. 임시객체는 참조로 가리킬수 없다.


	// 핵심 : 임시객체를 상수 참조로 가리킬수 있다.
	const Point& r3 = Point(1, 2); // 임시객체의 수명이 r3의 수명으로 연장됩니다.
								   // 가리킬수는 있는데.. 상수성이 추가된다..
	r3.x = 0;			// 그래서 이 코드가 에러!!!

	// C++11을 만들때 임시객체를 가리키고, 멤버도 변경하는게 필요 했다.
	// rvalue reference 문법 탄생..
	Point&& r4 = Point(1, 2);
	r4.x = 0; // ok.. 
}





