// 3 page ~
#include <iostream>
// �ٽ� 1. ��� �Լ� ȣ��� ��ü �ּ�(this)�� �����ؼ� ���޵˴ϴ�. - this call
//      2. static ��� �Լ��� this�� ���޵��� �ʽ��ϴ�. - this call �� �ƴ�.
class Point
{
	int x, y;
public:
	void set(int a, int b) // void set(Point* this, int a, int b)
	{						
		x = a;			  // 	this->x = a
		y = b;			  //	this->y = b;
	}						
	static void foo(int a)// void foo(int a)
	{
		x = a;		// this->x �� ����Ǿ�� �ϴµ�..this�� ����.
	}				// �׷��� error.
					// static ��� �Լ������� ��� ���� ���� �ȵ�.
};
int main()
{
	Point::foo(10); // ��ü ���� ȣ��..
					// push 10
					// call Point::foo

	Point p1, p2;

	p1.set(10, 20); // set(&p1, 10, 20) 
				// push	20
				// push 10	��¥ ���ڴ� ��������
				// mov  ecx, &p1
				// call Point::set  
}



