#include "cppmaster.h"
#include <vector>

class Point
{
	int x, y;
public:
	Point(int a, int b) { LOG_FUNCTION_NAME(); }
	~Point()            { LOG_FUNCTION_NAME(); }
	Point(const Point&) { LOG_FUNCTION_NAME(); }
};

int main()
{
	std::vector<Point> v;
	
	// �Ʒ� �ڵ尡 ����Ǹ� �Ҹ��ڰ� ��� ȣ��ɱ�� ?
	// vector�� ��� �ֱ�. 
	// 1. ��ü�� ������ �ֱ� - 2���� ��ü ���� 
	// Point pt(1, 2);
	// v.push_back(pt);

	// 2. �ӽð�ü�� �ֱ�
	//v.push_back( Point(1, 2) );

	// 3. ��ü�� ������ ������ ����
	//    ��ü�� ����� ���� ������ ���ڸ� �����Ѵ�

	v.emplace_back(1, 2);	// �� �Լ��� ���������� new Point(1,2) �ϰ� �˴ϴ�.
			// emplace_back �� �ڽ��� ���� ���ڸ� Point �� �����ڿ��� "����(forwarding)"
			// �ϰ� �ֽ��ϴ�.

	// STL �����̳ʿ� "�����Ÿ���� ������ �����Ѵٸ�"
	// push_xxx()�� ���� ����... emplace_xxx()�� �־��!!!
	// push_back(��ü) => emplace_back(����������)
	// push_front()    => emplace_front()
	// insert()        => emplace()

	std::cout << "-----" << std::endl;
}




