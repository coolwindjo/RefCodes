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
	// Point ��ü�� ���� �Ѱ��� ����� ������
	Point* p1 = new Point(1, 2);

	// Point ��ü�� ���� 10�� ����� ������
	// Point* p2 = new Point[10]; // 10���� ��ü�� ����Ʈ �����ڸ� ȣ���ؼ� �����Ǿ�� �մϴ�
							// ����Ʈ �����ڰ� �����Ƿ� error

	// C++11 ���ʹ� �Ʒ� ó�� �����մϴ�.
	// Point* p2 = new Point[10]{ {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0} };

	// ������ ȣ��� �޸� �Ҵ��� ���ÿ� �ϸ� �׻� �����մϴ�

	// 1. �޸𸮸� 10�� �Ҵ�
	Point* p2 = static_cast<Point*>(operator new(sizeof(Point) * 10));

	// 2. 10���� �޸� ������ ��ü�� ����
	for (int i = 0; i < 10; i++)
		new(&p2[i]) Point(0, 0); // std::construct_at(&p2[i], 0,0);

	//delete[] p2;

	// 3. �Ҹ��� ȣ��
	for (int i = 0; i < 10; i++)
		p2[i].~Point();    // std::destroy_at(&p2[i])

	// 4. �޸� ����
	operator delete(p2);
}








