
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
	
	pt.x = 10;				// OK
	// Point(1, 2).x = 10;		// Error. 임시객체는 등호의 왼쪽에 놓을 수 없다.
	// Point(1, 2).set(10, 20);// OK 임시객체가 상수는 아님
						

	Point* p1 = &pt;			// OK
	// Point* p2 = &Point(1, 2);	// Error. 임시객체는 주소연산자로 주소를 구할 수 없다.
								// CL은 허용함 (MFC에서 사용한 기법)
							

	Point& r1 = pt;				// OK
	// Point& r2 = Point(1, 2);	// Error. 임시객체는 참조로 가리킬 수 없다.

	// 핵심 : 임시객체를 상수 참조로 가리킬 수 있다.
	const Point& r3 = Point(1, 2); 	// 임시 객체의 수명이 r3의 수명으로 연장됩니다.
	// r3.x = 0;						// Error. 가리킬 수는 있지만... 상수성이 추가된다.

	// C++11을 만들 때, 임시객체를 가리키고, 멤버도 변경하는게 필요했다.
	// rvalue reference 문법 탄생
	Point&& r4 = Point(1, 2);
	r4.x = 0;	// OK
}





