// 1_rvalue3
#include <iostream>

// value category �� decltype
int main()
{
	int n = 0;
	int* p = &n;

	// ��Ģ 1. () �ȿ� �ɺ��� ������ : �ش� �ɺ��� ������ ���� Ÿ�� ����
	decltype(n) d1;	// int  d1
	decltype(p) d2;	// int* d2

	// ��Ģ 2. () �ȿ� �ɺ�+������ ���� ǥ������ ������
	//			�ش� ǥ������ lvalue �� �ɼ� ������ ����,, �ƴϸ� ��.
	decltype(*p)  d3; // int& d3;  �ʱⰪ�� ��� error
	decltype((n)) d4; // int& d4; 
	decltype(n+n) d5; // int  d5;
	decltype(++n) d6; // int& d6

	
	int x[3] = { 1,2,3 };
	
	decltype( x[0] ) d7; // x[0] = 10 �� �ȴ�... ����
						// int& d7
	
	// x[0] �� Ÿ���� �и� "int&" �Դϴ�.
	// �׷���, auto�� �캯�� �Ϻ��� ������ Ÿ������ �����ϸ� ������ �����մϴ�
	// �׷���, �캯�� "����, const, volatile" �Ӽ��� ������ Ÿ�԰���.
	auto a1 = x[0];

	const int c = 10;
	auto a2 = c; // a2�� Ÿ���� ?
	a2 = 20; // ok..  
}


