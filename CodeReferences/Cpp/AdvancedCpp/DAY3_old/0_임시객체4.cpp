#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};

// 4. 임시객체와 함수 반환값.

void f1(Point  pt) {} // call by value     : 복사본 생성
void f2(Point& pt) {} // call by reference : 복사본 생성 안됨.


Point pt(1, 2);
// 1. 값 리턴과 참조 리턴의 차이점..
//    지역변수는 참조리턴 하면 안된다.
Point foo()    // return by value : 임시객체 반환
{
	return pt; 
}
Point& goo()    // return by reference : 리턴용 임시객체를 만들지 말라는 표기법
{
	return pt;
}

Point& hoo()
{
	Point p(1, 2);
	return p;   // 버그.. 절대, 지역변수를 참조 리턴하지는 마세요..!!!
				// 지역변수는 반드시 값리턴만 해야 합니다
}
Point& koo(Point& p)
{
	return p; // 이런 코드는 아무 문제 없습니다. 그리고 널리 사용됩니다.
}				// 오늘 아주 자주 등장합니다.

int main()
{
//	int a;
//	std::cout << a << std::endl;  // 0

	Point& p = hoo();
	std::cout << p.x << std::endl;

	goo().x = 10; // ok.. pt.x = 10
	foo().x = 10; // error. (리턴용) 임시객체이므로 등호의 왼쪽에 올수 없다.

	Point p(0, 0);
	f1(p);
	f2(p);
}







