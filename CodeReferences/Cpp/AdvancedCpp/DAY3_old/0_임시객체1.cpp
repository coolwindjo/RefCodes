// ī�信�� 3���� �����ҽ� �����ø� �˴ϴ�.
// cafe.naver.com/cppmaster

#include <iostream>
#include <type_traits>

class Point
{
public:
	int x, y;

	Point(int a, int b)	{ std::cout << "Point()" << std::endl;	}
	~Point()            { std::cout << "~Point()" << std::endl;	}
};
// 1. �ӽð�ü����. ����� ��. ����..

int main()
{
//	Point pt(1, 2); // named object

//	Point (1, 2);	// unnamed object. �ӽð�ü(temporary)
					// ���� : ������ ��

	Point(1, 2), std::cout << "A" << std::endl;

	std::cout << "-------" << std::endl;

}






