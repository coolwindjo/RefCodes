#include <iostream>

class Empty
{
};
// �ٽ� : Empty �� ����� ������ ũ�Ⱑ 1�� ��������(Padding ���Խ� 4)
//		  Empty �� ���� ��ӹ����� ũ�Ⱑ 0���� ���˴ϴ�.
//		 Empty Base Class Optimization (EBCO)��� �̸��� ���� ���

struct Data
{
	Empty e;
	int   n;
};
struct Data2 : public Empty
{
	int   n;
};


int main()
{
	Data d;
	std::cout << sizeof(d) << std::endl;  // 8

	std::cout << sizeof(Data2) << std::endl; // 4
}





