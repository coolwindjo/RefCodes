// 10_EBCO -  73 page
#include <iostream>

// Empty Class : non static ��� ����Ÿ�� ���� Ŭ����, �����Լ��� ����� �Ѵ�.
//					ũ�Ⱑ 1�̴�.

// �Լ� ��ü,
// ĸ������ ���� ����ǥ���ĵ��� ���� empty Ŭ���� �Դϴ�.

class Empty 
{
	static int cnt;
public:
	void foo() {}
};
int Empty::cnt = 0;

struct Plus
{
	int operator()(int a, int b) { return a + b; }
};

int main()
{
	Empty e;
	std::cout << sizeof(e) << std::endl; // 1
}





