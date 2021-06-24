#include <iostream>

// ��� ���� ������
// �ٽ� 1. Member attribute�� Pointer ���� ����� ���
struct Point
{
	int x{ 0 };
	int y{ 0 };
};

int main()
{
	int n = 0;
	int* p1 = &n;	// �Ϲ� ������ ���� Pointer�����

	Point pt;
	int *p3 = &pt.x;	// �̹� �޸𸮿� �����ϴ� ��ü�� �ּ�

	// Member attribute�� Pointer
	// Pointer �ȿ��� Ư�� member�� offset�� ���ϴ� �ڵ�
	// C ���� offset_of() MACRO �� ���� ����
	int Point::*p2 = &Point::x;	// 0
	int Point::*p4 = &Point::y;	// 4

	// Member attribute pointer ��½� ���� cout���� ���� ���� printf ���!
	std::cout << p2 << ", " << p4 <<std::endl;	// 1, 1
	printf("%d, %d\n", p2, p4);

	// *p4 = 100;	// error: ���� ��ü�� ����. ���� offset ������ �ִ�.

	Point pt2;
	pt2.*p4 = 100;	// pt2.y = 100 �� �ǹ�
	std::cout << pt2.y <<std::endl;
}