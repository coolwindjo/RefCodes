// VC ���� ���� �ȵɶ�

// ������Ʈ �޴� - �Ӽ� �޴� ������

// "Windows SDK ����"�� "�÷��� ��������" ���� ���߼���..

// Mingw ����Ǯ��

// mingw/bin ������ "Path" ȯ�溯���� ����� �ּ���..

// Visual Studio �� �����Ϸ��̸�.. => cl.exe
// => ���� ��ư �����ð� => "visual studio ��������"
// => ������ ��� ������Ʈ �����ϼ���..

// C++20 ����� ����Ϸ���
// VS 2019 Preview ��ġ �ʿ�
// g++10.2







// DAY1.zip ����Ǯ���ּ���..

// 1_�������Լ�.cpp ���� ������

#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) : x(a), y(b) {}

	void set(int a, int b) { x = a; y = b; }

	void print() const	// ��� ��� �Լ�.
	{
		//x = 10;	// error. ��� ��� �Լ� �ȿ����� ��� ����� ���	

		std::cout << x << ", " << y << std::endl;
	}
};
int main()
{
	const Point pt(1, 2);

	pt.x = 10;		// error
	pt.set(10, 20);	// error
	pt.print();		// error. 
				// ȣ��ǰ� �Ϸ��� print()�� �ݵ�� ��� ��� �Լ� �̾�� �մϴ�.

	// �ٽ� : ��� ��ü�� "��� ��� �Լ��� ȣ��" �Ҽ� �ִ�.
}


