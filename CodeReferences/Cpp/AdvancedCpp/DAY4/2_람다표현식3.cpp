#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

/*
class ClosureType
{
public:
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
	// static ��� �Լ����� "��� ����Լ�"��� ������ ������� �ʽ��ϴ�.
	static inline auto helper()(int a, int b)
	{
		return a + b;
	}	
	// ��ü�� �Լ� �����ͷ� ��ȯ�ɼ� �ֵ��� ��ȯ ������ �Լ� ����
	typedef int(*F)(int, int);

	operator F() { return &Closure::helper; } // �׷���, operator() �Լ��� ����Լ��̹Ƿ�
												// this�� �߰��Ǵ� �Լ�..
};
*/

class ClosureType
{
	int v1, v2;
public:
	ClosureType(int v1, int v2) : v1(v1), v2(v2) {}

	inline auto operator()(int a, int b) const
	{
		return a + b + v1 + v2;
	}
	static inline auto helper()(int a, int b)
	{
		return a + b + v1 + v2; // error. static ��� �Լ��� ��� ����Ÿ ������ �ȵȴ�
	}
	typedef int(*F)(int, int);
	operator F() { return &Closure::helper; } 
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	// ����ǥ������ �Լ� �����Ϳ� ������ �ֽ��ϴ�.
	//int(*f)(int, int) = [](int a, int b) { return a + b; }; 
					// ClosureType().operator �Լ�������Ÿ��() 

	int v1 = 10, v2 = 20;
	int(*f)(int, int) = [v1, v2](int a, int b) { return a + b; };

	// ��� : ���������� "ĸ�� ���� ���� ����ǥ���ĸ�" �Լ� �����ͷ� ��ȯ���� �մϴ�.
	//			ĸ���� ���� ǥ������ �Լ������ͷ� ��ȯ�ɼ� �����ϴ�.
}








