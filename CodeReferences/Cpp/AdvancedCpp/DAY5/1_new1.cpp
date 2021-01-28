// 카페에서 5일차 사전소스 받으시면 됩니다.

#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	Point()				: x(0), y(0) { LOG_FUNCTION_NAME(); }
	Point(int a, int b) : x(a), y(b) { LOG_FUNCTION_NAME(); }
	~Point()						 { LOG_FUNCTION_NAME(); }
};

int main()
{
	// new 가 하는일
	// 1. 메모리 할당
	// 2. 생성자 호출
	//Point* p1 = new Point(1, 2);

	// delete
	// 1. 소멸자 호출
	// 2. 메모리 해지
	//delete p1;

	// 1. 생성자 호출없이 메모리만 할당
	Point* p1 = static_cast<Point*>( operator new( sizeof(Point) ) );

	// 2. 이미 할당된 메모리에 생성자만 호출
	new(p1) Point(1, 2); // C++20 : std::construct_at(p1, 1, 2)

	// 3. 소멸자만 호출
	p1->~Point();        // C++17 : std::destroy_at(p1)

	// 4. 소멸자 호출없이 메모리만 삭제
	operator delete(p1);
}
// malloc : 메모리만 할당
// new    : 객체 생성 ( 메모리 할당 + 생성자 호출 )

// new Point(1,2)          : 새로운 메모리에 Point 객체를 만들어 달라.
// new(address) Point(1,2) : 기존에 할당해놓은 address 주소 메모리에 객체를 만들어 달라
//  ==> Placement new(위치지정 new )

// 리눅스에서 공유메모리를 할당하려고 합니다.
// OS의 메모리 할당하는 시스템 콜 : 
Queue* pQueue = (Queue*)mmap(sizeof(Queue));

// 이제 IPC 를 객체지향으로 하기 위해.. 공유메모리에 할당된 메모리 공간에
// 객체생성(생성자호출)을 합니다
new(pQueue) Queue;

// 이 기술의 핵심
// "메모리 할당 방식을 변경할수 있게 하겠다는 의도.... "







