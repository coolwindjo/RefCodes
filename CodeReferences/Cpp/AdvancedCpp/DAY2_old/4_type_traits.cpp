#include <iostream>

// ���ø� ���� T�� ���� �پ��� �Ӽ��� �����ϴ� ��� - "type traits" ��� �մϴ�

template<typename T> void printv(const T& v)
{
	if ( T �� ������ Ÿ���̸� )

		std::cout << v << " : " << *v << std::endl;
	else
		std::cout << v << std::endl;
}

int main()
{
	int n = 10;
	double d = 3.4;

	printv(n);
	printv(d);
	printv(&n);
}

