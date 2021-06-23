#define _ENABLE_ATOMIC_ALIGNMENT_FIX
#include <iostream>
#include <thread>
#include <atomic>

// 크기가 8바이트 입니다.
struct Point
{
	int x;
	int y;
//	int z; // 이 멤버 때문에 12byte가 됩니다.

	Point(const Point& p) : x(p.x), y(p.y) {}
};

std::atomic<Point> pt;

int main()
{
	Point p = pt.load();// Point가 trivially copyable 하지 많으면 
						// 이 순간 단순한 메모리 복사가 아닌
						// 복사 생성자의 호출이 요구 됩니다.
	std::cout << pt.is_lock_free() << std::endl; //  
}
