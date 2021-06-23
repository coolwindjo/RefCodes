#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) : x(a), y(b) {}

	void set(int a, int b) { x = a; y = b; }

	void print() const	
	{
		// x = 10;	// error: const method 안에서 모든 attribute는 const!		

		std::cout << x << ", " << y << std::endl;
	}
};

int main()
{
	const Point pt(1, 2);	// Const object

	// pt.x = 10;	// error 
	// pt.set(10, 20);	// error
	pt.print();		// Const object는 "const method만 호출" 할 수 있다.	
}


