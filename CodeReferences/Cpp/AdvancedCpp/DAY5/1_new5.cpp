#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	Point()				: x(0), y(0) { LOG_FUNCTION_NAME(); }
	Point(int a, int b) : x(a), y(b) { LOG_FUNCTION_NAME(); }
	~Point() { LOG_FUNCTION_NAME(); }
};

int main()
{
	// 아래 4줄의 코드에서.. 메모리할당 방식을 변경하려면 몇줄을 수정해야 할까요?
	// 할당하는 코드뿐 아니라 해지 하는 코드도 수정되어야 합니다.
	//Point* p1 = static_cast<Point*>(operator new(sizeof(Point)));
	//new(p1) Point(1, 2);
	//p1->~Point();
	//operator delete(p1);

	// 메모리 할당기 : 메모리 할당과 해지를 책임지는 클래스

	std::allocator<Point> ax; // C++ 표준 할당기
	//std::MyAlloc<Point> ax;

	Point* p1 = ax.allocate(1); // operator new(sizeof(Point)*1)

	ax.construct(p1, 1, 2);  // 생성자 호출
	
	ax.destroy(p1);	// 소멸자 호출
	
	ax.deallocate(p1, 1);	// 메모리 해지.

}



