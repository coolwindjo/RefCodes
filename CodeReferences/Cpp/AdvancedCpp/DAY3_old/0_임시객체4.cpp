#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};

// 4. �ӽð�ü�� �Լ� ��ȯ��.

void f1(Point  pt) {} // call by value     : ���纻 ����
void f2(Point& pt) {} // call by reference : ���纻 ���� �ȵ�.


Point pt(1, 2);
// 1. �� ���ϰ� ���� ������ ������..
//    ���������� �������� �ϸ� �ȵȴ�.
Point foo()    // return by value : �ӽð�ü ��ȯ
{
	return pt; 
}
Point& goo()    // return by reference : ���Ͽ� �ӽð�ü�� ������ ����� ǥ���
{
	return pt;
}

Point& hoo()
{
	Point p(1, 2);
	return p;   // ����.. ����, ���������� ���� ���������� ������..!!!
				// ���������� �ݵ�� �����ϸ� �ؾ� �մϴ�
}
Point& koo(Point& p)
{
	return p; // �̷� �ڵ�� �ƹ� ���� �����ϴ�. �׸��� �θ� ���˴ϴ�.
}				// ���� ���� ���� �����մϴ�.

int main()
{
//	int a;
//	std::cout << a << std::endl;  // 0

	Point& p = hoo();
	std::cout << p.x << std::endl;

	goo().x = 10; // ok.. pt.x = 10
	foo().x = 10; // error. (���Ͽ�) �ӽð�ü�̹Ƿ� ��ȣ�� ���ʿ� �ü� ����.

	Point p(0, 0);
	f1(p);
	f2(p);
}







