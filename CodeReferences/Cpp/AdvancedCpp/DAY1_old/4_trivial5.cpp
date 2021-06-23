#define _ENABLE_ATOMIC_ALIGNMENT_FIX
#include <iostream>
#include <thread>
#include <atomic>

// ũ�Ⱑ 8����Ʈ �Դϴ�.
struct Point
{
	int x;
	int y;
//	int z; // �� ��� ������ 12byte�� �˴ϴ�.

	Point(const Point& p) : x(p.x), y(p.y) {}
};

std::atomic<Point> pt;

int main()
{
	Point p = pt.load();// Point�� trivially copyable ���� ������ 
						// �� ���� �ܼ��� �޸� ���簡 �ƴ�
						// ���� �������� ȣ���� �䱸 �˴ϴ�.
	std::cout << pt.is_lock_free() << std::endl; //  
}
