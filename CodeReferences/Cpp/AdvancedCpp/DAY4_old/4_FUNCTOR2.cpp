// 4_FUNCTOR1
#include <iostream>

// �Լ� ��ü(Function Object, Functor )
// () �����ڸ� ������ �ؼ� �Լ� ó�� ��밡���� ��ü
// "���¿� ����"�� ������ �Լ�!!
// ���򿡴� "�Լ���ü"��� ��� ��� "callable object"

// callable object  : () �� ȣ�� ������ ����, - �Լ�, �Լ���ü, ����ǥ����

class URandom
{
	int history[10];
public:
	void reset_history() {}
	int operator()()
	{
		// ��� ����Ÿ�� ���ؼ� ���¸� ����
		return rand() % 10;
	}
};

int main()
{
	URandom urand; 
	urand(); // �Լ� ó�� ����Ҽ� �ְ� �Ϸ���
			 // urand.operator()() �� �Ǹ� �˴ϴ�.
			 // urand.next()

	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}