#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};

// 3. �ӽð�ü�� �Լ� ����..
// void foo( Point& pt) {}  : ���ڷ� �ӽð�ü�� ������ ���� ǥ��..

void foo(const Point& pt) {}

int main()
{
//	Point pt(1, 2);
//	foo(pt);

	// �Լ� ���ڷθ� ����� ��ü�� �ʿ� �ϸ�
	// �ӽð�ü�� ����ϴ°� ȿ�����̴�.
	foo( Point(1, 2) );



	std::cout << "-----" << std::endl;
}











