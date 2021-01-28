int x = 10;

int& foo(int a, int b) { return x; }

int main()
{
	auto ret1 = foo(10, 20);
				// int& ������ auto�� ������ �����ϰ� Ÿ�� ����
				// int ret1 = foo(10, 20);

	// decltype(�Լ�ȣ���) : �Լ� ȣ���� ����� ������ Ÿ�� ����(��ȯŸ��)
	//						���� �Լ��� ȣ��Ǵ� ���� �ƴ�.
	decltype( foo(10, 20) ) ret2 = foo(10, 20);
				// int& ret2 = foo(10, 20);    �� �ǹ�..

	// C++14 ���� ���� ���ο� ���
	// �캯�� ǥ������ auto �ڸ��� �־� �޶�.
	// �ᱹ "�캯���� Ÿ���߷�" ��, auto �߷��� �ƴ� decltype �߷� ��� ���.
	decltype(auto) ret3 = foo(10, 20);
			// int& ret3 = foo(10, 20); 

	auto&& ret4 = foo(10, 20); // �캯�� ���������̸�(lvalue)�̹Ƿ� 
							// int& ret4 = foo(10,20);
							// ������ �̸�.. rvalue �̹Ƿ�
							// int ret4 = foo(10,20);
}