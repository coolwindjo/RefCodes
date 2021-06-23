#include <thread>
#include <memory>
#include <iostream>

class Point
{
	int x, y;
public:
	Point(int a, int b) { LOG_FUNCTION_NAME(); }
	~Point()			{ LOG_FUNCTION_NAME(); }
	Point(const Point&) { LOG_FUNCTION_NAME(); }
};

int goo() { return 10; }

void foo( std::shared_ptr<Point> sp,  int b) {}

int main()
{
	// �Ʒ� �ڵ�� ������ �ڵ��ϱ�� ?
	foo( std::shared_ptr<Point>( new Point(1, 2) ),  goo()  );


	// ��ü�� ������.. ��ü�� �����ϴ� ����Ʈ �������� ������
	// "�ϳ��� ����"���� �ϴ� ���� �����Ѵ�.

	std::shared_ptr<Point> sp1(new Point(1, 2)); // �̷��� ���� ����
	std::shared_ptr<Point> sp2 = std::make_shared<Point>(1, 2); // �̷��� �϶�°�
									// 1. Point* p = new Point(1,2) �� �����
									// 2. return std::shared_ptr<Point>(p) ó�� ��ȯ

	foo( std::make_shared<Point>(1, 2), goo());

}








