#include <iostream>

void foo(int& a)       { std::cout << "int&"       << std::endl; }
void foo(const int& a) { std::cout << "const int&" << std::endl; }
void foo(int&& a)      { std::cout << "int&&"      << std::endl; }

int main()
{
	int n = 10;

	foo(n);	// 1�� ȣ��, 1���� ������ 2�� ȣ��
	foo(10);// 3�� ȣ��, ������ 2��.. 

	int& r1 = n;
	foo(r1);	// 1�� ȣ��, ������ 2�� ȣ��

	int&& r2 = 10;  // 10�� �̸��� ���� - rvalue
					// r2�� �̸��� �ִ� - lvalue �̴�.
	// Ÿ�԰� value �Ӽ��� �򰥸��� ������
	
	//			Ÿ��			value �Ӽ�
	// 10		int				rvalue
	// r2		int&&			lvalue
	// void foo(int&&) : int&& Ÿ���� �ްڴٴ°� �ƴ϶�!!!
	//					rvalue ǥ������ ���ڷ� �ްڴٴ� �ǹ�.

	foo(r2);	// 1��

	// r2�� 3������ �������� r2�� (1) Ÿ���� �����ؾ� �Ѵ�.
	//							  (2) value �Ӽ��� �����ؾ� �Ѵ�. => ��!!!
	foo( static_cast<int&&>(r2) ); // �� �ڵ�� Ÿ�� ĳ������ �ƴ� 
								// value casting �Դϴ�.
								// cppreference.com ���� static_cast �˻��غ�����
						// lvalue(glvalue) => rvalue(��Ȯ���� xvalue)�� ĳ����
}







