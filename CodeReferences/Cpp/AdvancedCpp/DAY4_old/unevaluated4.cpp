#include <iostream>

class Test 
{
public:
//	void resize() {}
};

// �ٽ� : SFINAE ����� "������ �������� ������ ����" �ϴ� �Լ� ���ø� ����
//		resize() �Լ��� �ִ��� ���簡 �ʿ� 

// �Ʒ� ���ø��� T �ȿ� resize()�� ������ ����, ������ (ġȯ)���� �Դϴ�.
template<typename T> 
int  check( decltype( T().resize() )* p );
		 

template<typename T> char check(...);

int main()
{
	int n = sizeof( check<Test>(0) );

	std::cout << n << std::endl;
}



