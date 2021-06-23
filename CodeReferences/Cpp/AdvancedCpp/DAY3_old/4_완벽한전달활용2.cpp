#include <thread>
#include <memory>
#include <iostream>

class Point
{
	int x, y;
public:
	Point(int a, int b) { LOG_FUNCTION_NAME(); }
	~Point()			{ LOG_FUNCTION_NAME(); }
	Point(const Point&) { LOG_FUNCTION_NAME(); }
};

int goo() { return 10; }

void foo( std::shared_ptr<Point> sp,  int b) {}

int main()
{
	// 아래 코드는 안전한 코드일까요 ?
	foo( std::shared_ptr<Point>( new Point(1, 2) ),  goo()  );


	// 객체의 생성과.. 객체를 관리하는 스마트 포인터의 생성은
	// "하나의 동작"으로 하는 것이 안전한다.

	std::shared_ptr<Point> sp1(new Point(1, 2)); // 이렇게 하지 말고
	std::shared_ptr<Point> sp2 = std::make_shared<Point>(1, 2); // 이렇게 하라는것
									// 1. Point* p = new Point(1,2) 로 만들고
									// 2. return std::shared_ptr<Point>(p) 처럼 반환

	foo( std::make_shared<Point>(1, 2), goo());

}








