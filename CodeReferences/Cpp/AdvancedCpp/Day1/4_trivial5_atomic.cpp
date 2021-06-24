#define _ENABLE_ATOMIC_ALIGNMENT_FIX
#include <iostream>
#include <thread>
#include <atomic>

struct Point
{
	int x;
	int y;	// 8 byte
	// int z;	// 12 byte

	Point() = default;	// necessary
	/*/
	Point(const Point &pt) : x(pt.x), y(pt.y) {}
	/*/
	Point(const Point &pt) = default;
	//*/
};

std::atomic<Point> pt;

int main()
{
	Point p = pt.load();	// CPU lock 이용 가능 여부
							// 이 순간 단순한 Memory 복사가 아닌,
							// Copy Constructor 호출이 요구된다.

	std::cout << std::boolalpha << pt.is_lock_free() << std::endl;
}
