// ī�信�� 5���� �����ҽ� �����ø� �˴ϴ�.

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
	// new �� �ϴ���
	// 1. �޸� �Ҵ�
	// 2. ������ ȣ��
	//Point* p1 = new Point(1, 2);

	// delete
	// 1. �Ҹ��� ȣ��
	// 2. �޸� ����
	//delete p1;

	// 1. ������ ȣ����� �޸𸮸� �Ҵ�
	Point* p1 = static_cast<Point*>( operator new( sizeof(Point) ) );

	// 2. �̹� �Ҵ�� �޸𸮿� �����ڸ� ȣ��
	new(p1) Point(1, 2); // C++20 : std::construct_at(p1, 1, 2)

	// 3. �Ҹ��ڸ� ȣ��
	p1->~Point();        // C++17 : std::destroy_at(p1)

	// 4. �Ҹ��� ȣ����� �޸𸮸� ����
	operator delete(p1);
}
// malloc : �޸𸮸� �Ҵ�
// new    : ��ü ���� ( �޸� �Ҵ� + ������ ȣ�� )

// new Point(1,2)          : ���ο� �޸𸮿� Point ��ü�� ����� �޶�.
// new(address) Point(1,2) : ������ �Ҵ��س��� address �ּ� �޸𸮿� ��ü�� ����� �޶�
//  ==> Placement new(��ġ���� new )

// ���������� �����޸𸮸� �Ҵ��Ϸ��� �մϴ�.
// OS�� �޸� �Ҵ��ϴ� �ý��� �� : 
Queue* pQueue = (Queue*)mmap(sizeof(Queue));

// ���� IPC �� ��ü�������� �ϱ� ����.. �����޸𸮿� �Ҵ�� �޸� ������
// ��ü����(������ȣ��)�� �մϴ�
new(pQueue) Queue;

// �� ����� �ٽ�
// "�޸� �Ҵ� ����� �����Ҽ� �ְ� �ϰڴٴ� �ǵ�.... "







