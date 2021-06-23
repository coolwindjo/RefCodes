#include <iostream>

// ��� ���� ������
// �ٽ� 1. ��� ������ ������ ���� ����� ���.
struct Point
{
	int x{ 0 };
	int y{ 0 };
};
int main()
{
	int n = 0;
	int* p1 = &n; // �Ϲ� ������ ���� ������ ���� �����

	Point pt;
	int* p2 = &pt.x; // �̹� �޸𸮿� �����ϴ� ��ü�� �ּ�.

	// ��� ������ ������
	// Point �ȿ��� Ư�� ����� offset �� ���ϴ� �ڵ�.

	// C ����� offset_of() ��ũ���� �ǹ�.
	int Point::*p3 = &Point::x; // 0
	int Point::*p4 = &Point::y; // 4

	// ��� ���� ������ ��½�.. ���� �Ʒ� ó�� cout���� ���� ����
	// printf()����ϼ���
	// std::cout << p3 << ", " << p4 << std::endl;
	printf("%d, %d\n", p3, p4);
	
//	*p4 = 100; // error.  ���� ��ü�� ����. ���� offset ������ �ִ�.

	Point pt2;
	pt2.*p4 = 100; // pt2.y = 100  �� �ǹ� �Դϴ�.

	std::cout << pt2.y << std::endl; // 100

}







// Ctrl + F5