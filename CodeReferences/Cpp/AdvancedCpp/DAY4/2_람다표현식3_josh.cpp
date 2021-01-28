#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

// class ClosureType
// {
// public:
// 	inline auto operator()(int a, int b) const
// 	{
// 		return a + b;
// 	}

// 	// static Member �Լ����� "��� Member�Լ�" ��� ������ ������� �ʽ��ϴ�.
// 	static inline auto helper()(int a, int b)
// 	{
// 		return a + b;
// 	}

// 	// ��ü�� �Լ� Pointer�� ��ȯ �� �� �ֵ��� ��ȯ ������ �Լ� ����
// 	typedef int(*f)(int, int);
// 	operator F() { return &Closure::operator(); }	// �׷���, operator() �Լ��� Member�Լ� Pointer�� �Ϲ� �Լ� Pointer�� ȣȯ���� �ʴ´�.
// 														// this �� �߰��Ǵ� �Լ��̹Ƿ�...
// };

class ClosureType
{
public:
	inline auto operator()(int a, int b) const
	{
		return a + b + v1 + v2;
	}

	// static Member �Լ����� "��� Member�Լ�" ��� ������ ������� �ʽ��ϴ�.
	static inline auto helper()(int a, int b)
	{
		return a + b + v1 + v2;
	}

	// ��ü�� �Լ� Pointer�� ��ȯ �� �� �ֵ��� ��ȯ ������ �Լ� ����
	typedef int(*f)(int, int);
	operator F() { return &Closure::operator(); }	// �׷���, operator() �Լ��� Member�Լ� Pointer�� �Ϲ� �Լ� Pointer�� ȣȯ���� �ʴ´�.
														// this �� �߰��Ǵ� �Լ��̹Ƿ�...
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	// Lambda expression�� �Լ� Pointer�� ���� �� �ֽ��ϴ�.
	// int(*f)(int, int) = [](int a, int b) { return a + b; };
						// ClosureType().operator �Լ�PointerType():	��ü�� �Լ� Pointer�� ����??

	// int v1 = 10;
	// int v2 = 20;
	// int(*f)(int, int) = [v1, v2](int a, int b) { return a + b; };

	// ���: ���� ������ "Capture���� ���� Lambda expression��" �Լ� Pointer�� ��ȯ���� �մϴ�.
				// Capture�� Lambda expression�� �Լ� Pointer�� ��ȯ�� �� �����ϴ�.
	return 0;
}
