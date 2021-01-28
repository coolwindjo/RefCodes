#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	//Point() : x(0), y(0) { LOG_FUNCTION_NAME(); }
	Point(int a, int b) : x(a), y(b) { LOG_FUNCTION_NAME(); }
	~Point() { LOG_FUNCTION_NAME(); }
};

int main()
{
	// Point 객체를 힙에 한개만 만들어 보세요
	Point* p1 = new Point(1, 2);

	// Point 객체를 힙에 10개 만들어 보세요
	// Point* p2 = new Point[10]; // 10개의 객체가 디폴트 생성자를 호출해서 생성되어야 합니다
							// 디폴트 생성자가 없으므로 error

	// C++11 부터는 아래 처럼 가능합니다.
	// Point* p2 = new Point[10]{ {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0} };

	// 생성자 호출과 메모리 할당을 동시에 하면 항상 불편합니다

	// 1. 메모리만 10개 할당
	Point* p2 = static_cast<Point*>(operator new(sizeof(Point) * 10));

	// 2. 10개의 메모리 공간에 객체를 생성
	for (int i = 0; i < 10; i++)
		new(&p2[i]) Point(0, 0); // std::construct_at(&p2[i], 0,0);

	//delete[] p2;

	// 3. 소멸자 호출
	for (int i = 0; i < 10; i++)
		p2[i].~Point();    // std::destroy_at(&p2[i])

	// 4. 메모리 해지
	operator delete(p2);
}








