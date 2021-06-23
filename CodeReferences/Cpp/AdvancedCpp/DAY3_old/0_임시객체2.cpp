
#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};
int main()
{
	Point pt(1, 2);
	
	pt.x = 10;			// ok
//	Point(1, 2).x = 10;	// error. �ӽð�ü�� ��ȣ�� ���ʿ� ������ ����.				
//	Point(1, 2).set(10, 20); // ok.. ��, �ӽð�ü�� ����� �ƴմϴ�.

	Point* p1 = &pt;			// ok
//	Point* p2 = &Point(1, 2);	// error. �ӽð�ü�� �ּҿ����ڷ� �ּҸ� ���Ҽ� ����.						

	Point& r1 = pt;			 // ok
//	Point& r2 = Point(1, 2); // error. �ӽð�ü�� ������ ����ų�� ����.


	// �ٽ� : �ӽð�ü�� ��� ������ ����ų�� �ִ�.
	const Point& r3 = Point(1, 2); // �ӽð�ü�� ������ r3�� �������� ����˴ϴ�.
								   // ����ų���� �ִµ�.. ������� �߰��ȴ�..
	r3.x = 0;			// �׷��� �� �ڵ尡 ����!!!

	// C++11�� ���鶧 �ӽð�ü�� ����Ű��, ����� �����ϴ°� �ʿ� �ߴ�.
	// rvalue reference ���� ź��..
	Point&& r4 = Point(1, 2);
	r4.x = 0; // ok.. 
}





