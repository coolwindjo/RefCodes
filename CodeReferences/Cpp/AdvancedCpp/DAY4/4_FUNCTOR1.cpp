// 4_FUNCTOR1
#include <iostream>

// �ٽ� : �Ϲ� �Լ��� "������ ������ ���¸� ������ ����"

// 0 ~ 9 ������ "�ߺ����� ����" ������ ��ȯ�ϴ� �Լ�
int urand()
{
	return rand() % 10;
}

int main()
{
	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}