#include <algorithm>
#include <functional>  
#include <vector>
#include <iostream>
using namespace std;


class ClosureType
{
	int v1;
	int v2;
public:
	ClosureType(int v1, int v2) : v1(v1), v2(v2) {}

	inline auto operator()(int a, int b) //const
	{
		v1 = 1000;
		return a + b + v1 + v2;
	}
};
int main()
{
	int v1 = 10, v2 = 20; // ��������

//	auto f1 = [v1, v2](int a, int b) { v1 = 10;  return a + b + v1 + v2; };
			// ClosureType(v1, v2)  �� ����...

	// mutable ����ǥ���� : () �����ڸ� �� ��� ����Լ��� �ش޶�"
	//auto f1 = [v1, v2](int a, int b) mutable { v1 = 1000;  return a + b + v1 + v2; };

	// v1, v2�� ������ ĸ��
	auto f1 = [&v1, &v2](int a, int b)  { v1 = 1000;  return a + b + v1 + v2; };

	std::cout << sizeof(f1) << std::endl; // 8
}






