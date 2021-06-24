#include <iostream>

// 멤버 변수 포인터
// 핵심 1. Member attribute의 Pointer 변수 만드는 방법
struct Point
{
	int x{ 0 };
	int y{ 0 };
};

int main()
{
	int n = 0;
	int* p1 = &n;	// 일반 변수에 대한 Pointer만들기

	Point pt;
	int *p3 = &pt.x;	// 이미 메모리에 존재하는 객체의 주소

	// Member attribute의 Pointer
	// Pointer 안에서 특정 member의 offset을 구하는 코드
	// C 에서 offset_of() MACRO 와 같은 동작
	int Point::*p2 = &Point::x;	// 0
	int Point::*p4 = &Point::y;	// 4

	// Member attribute pointer 출력시 절대 cout으로 하지 말고 printf 사용!
	std::cout << p2 << ", " << p4 <<std::endl;	// 1, 1
	printf("%d, %d\n", p2, p4);

	// *p4 = 100;	// error: 아직 객체가 없다. 단지 offset 정보만 있다.

	Point pt2;
	pt2.*p4 = 100;	// pt2.y = 100 을 의미
	std::cout << pt2.y <<std::endl;
}