#include <iostream>
#include <type_traits> // C++11 �� type traits ���̺귯��.
						// Ÿ�Կ� ���� �پ��� ���� ����.

// �ٽ� : trivial ���θ� �����ϴ� ���.

class Test
{
	int data = 10; // �� �ڵ� ������ �����Ϸ��� ���� ����Ʈ �����ڴ�
					// trivial ���� �ʽ��ϴ�.
public:
	void goo() {}
//	virtual void foo() {}

//	Test(){} // ������ �ƹ� �ڵ嵵 ������, �����Ϸ��� �����ڰ� �ϴ����� �ִٰ�
				// �����ذ� �˴ϴ�. trivial ���� �ʽ��ϴ�.

	Test() = default; // C++11 �� ���ο� ����
					// ���ھ���(����Ʈ) �����ڸ� ����� �޶�� �ǹ�.
			// : data(10) {}

	Test(int a, int b) {}
};

int main()
{
	Test t;
	bool b = std::is_trivially_default_constructible_v<Test>;

	

	std::cout << b << std::endl;
}