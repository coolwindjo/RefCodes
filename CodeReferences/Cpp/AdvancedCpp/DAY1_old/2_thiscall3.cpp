#include <iostream>

// 멤버 변수 포인터
// 핵심 1. 멤버 변수의 포인터 변수 만드는 방법.
struct Point
{
	int x{ 0 };
	int y{ 0 };
};
int main()
{
	int n = 0;
	int* p1 = &n; // 일반 변수에 대한 포인터 변수 만들기

	Point pt;
	int* p2 = &pt.x; // 이미 메모리에 존재하는 객체의 주소.

	// 멤버 변수의 포인터
	// Point 안에서 특정 멤버의 offset 을 구하는 코드.

	// C 언어의 offset_of() 매크로의 의미.
	int Point::*p3 = &Point::x; // 0
	int Point::*p4 = &Point::y; // 4

	// 멤버 변수 포인터 출력시.. 절대 아래 처럼 cout으로 하지 말고
	// printf()사용하세요
	// std::cout << p3 << ", " << p4 << std::endl;
	printf("%d, %d\n", p3, p4);
	
//	*p4 = 100; // error.  아직 객체가 없다. 단지 offset 정보만 있다.

	Point pt2;
	pt2.*p4 = 100; // pt2.y = 100  의 의미 입니다.

	std::cout << pt2.y << std::endl; // 100

}







// Ctrl + F5