#include <iostream>

class Test
{
public:
	//void foo() {} // error  &, && ������ ���� ����� ����.

	void foo() &    // �̸� �ִ� ��ü�� ȣ���Ҷ�..
	{
		std::cout << "foo &" << std::endl; 
	}
	void foo() && // �̸����� ��ü(�ӽð�ü��) ȣ���Ҷ�
	{
		std::cout << "foo &&" << std::endl;
	}
};

int main()
{
	Test t;
	t.foo(); // foo() &

	Test().foo(); // foo() &&
}

