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
	// �Ʒ� 4���� �ڵ忡��.. �޸��Ҵ� ����� �����Ϸ��� ������ �����ؾ� �ұ��?
	// �Ҵ��ϴ� �ڵ�� �ƴ϶� ���� �ϴ� �ڵ嵵 �����Ǿ�� �մϴ�.
	//Point* p1 = static_cast<Point*>(operator new(sizeof(Point)));
	//new(p1) Point(1, 2);
	//p1->~Point();
	//operator delete(p1);

	// �޸� �Ҵ�� : �޸� �Ҵ�� ������ å������ Ŭ����

	std::allocator<Point> ax; // C++ ǥ�� �Ҵ��
	//std::MyAlloc<Point> ax;

	Point* p1 = ax.allocate(1); // operator new(sizeof(Point)*1)

	ax.construct(p1, 1, 2);  // ������ ȣ��
	
	ax.destroy(p1);	// �Ҹ��� ȣ��
	
	ax.deallocate(p1, 1);	// �޸� ����.

}



