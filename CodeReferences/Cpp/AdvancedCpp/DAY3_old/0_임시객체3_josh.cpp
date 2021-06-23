#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};

// 3. 임시 객체와 함수 인자
void foo(const Point& pt) {}
// void foo(Point& pt) {}	// 인자로 임시 객체를 받을 수 없는 표현

int main()
{
	Point pt(1, 2);
	foo(pt);

	// 함수 인자로만 사용할 객체가 필요하면, 임시객체를 사용하는게 효율적!
	foo( Point(1, 2) );

	std::cout << "-----" << std::endl;
}





