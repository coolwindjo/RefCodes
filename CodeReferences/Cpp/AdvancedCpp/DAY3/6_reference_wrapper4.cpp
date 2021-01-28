#include <iostream>
#include <functional>
using namespace std::placeholders;

void foo(int& a, int n) { a = 300; }

int main()
{	
	std::function<void(int)> f; // C++11 function
								// �Լ������� ��Ȱ..

	// bind�� ���ڸ� "������ �ƴ� ��"���� �����ϰ� �˴ϴ�. ������ �Ʒ� {}�� �ִٰ� �����غ�����
//	{
		int n = 0;

//		f = std::bind(&foo, n, _1); // 1��° ���ڸ� "n"���� ����������� ?
									//	"n�� ��(0)"���� ����������� ?  =====> ����...
		f = std::bind(&foo, std::ref(n), _1); // ok.. ������ ����..
//	}

	f(10); // foo(n, 10) �� �ƴϰ�
		   // foo(0, 10) �� ǥ��..

	std::cout << n << std::endl; // 
}