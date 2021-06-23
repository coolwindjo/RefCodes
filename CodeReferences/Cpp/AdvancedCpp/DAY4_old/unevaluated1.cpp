// unevaluated1.cpp
#include <iostream>

// �ٽ� 
// �򰡵��� ���� ǥ����(unevaluated expression)

int foo(int a, int b); // { return 0; }

int main()
{
	int a = 0;

	// sizeof : �Լ��� �ƴ� ������, ������ �ð��� ũ�⸦ ���ϴ� ��.
	int n1 = sizeof(a);		// 4
	int n2 = sizeof(int);	// 4
	int n3 = sizeof(&foo);	// 4 - �Լ��ּ��� ũ��(��, ������ Ÿ���� ũ��)

//	int n4 = sizeof(foo);	// error. - �Լ� ��ü�� ũ��� ���Ҽ� ����.
							// ���� - �����Ϸ��� �Լ� �������ε� �Լ��� ȣ���Ҽ� �ִµ�
							// �Լ��� ũ�⸦ ���Ϸ��� "�Ϻ��� ������ ����" �Ǿ�� �Ѵ�.

	// �ٽ� : sizeof(�Լ�ȣ���) :�Լ�ȣ���� ����� ������ Ÿ���� ũ��.
	int n5 = sizeof( foo(1, 2) ); // foo�� ��ȯ Ÿ���� int�� ũ�� - 4

	// �򰡵��� ���� ǥ����(unevaluated expression)
	// => �Լ� ȣ��� ���� ǥ������ �����δ� ������� �ʰ�, ������ �ð����� Ȱ��Ǵ°�
	// 4���� �ֽ��ϴ�. ( sizeof, noexcept, decltype, typeid)
	bool b = noexcept( foo(1, 2 ) );
	decltype(foo(1, 2)) d1;
	std::cout << typeid(foo(1, 2)).name() << std::endl;

}








