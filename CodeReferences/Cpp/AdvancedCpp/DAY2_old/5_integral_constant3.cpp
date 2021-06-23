#include <iostream>

// �Ʒ� �ڵ尡 2000�⵵�� "modern C++ design" å�� ���ڰ� ���� �ڵ��Դϴ�.
template<int N> struct int2type
{
	enum { value = N };
};

int main()
{
	foo(0);
	foo(1); // 0,1 �� ���� Ÿ��.. foo(0), foo(1) �� ���� �Լ� ȣ��

	int2type<0> t0;
	int2type<1> t1;

	foo(t0);
	foo(t1); // t0�� t1�� �ٸ� Ÿ��. foo(t0), foo(t1) �� �ٸ� �Լ� ȣ��.
			// 77, 78 �� ���� Ÿ��
			// int2type<77>, int2type<78>
}