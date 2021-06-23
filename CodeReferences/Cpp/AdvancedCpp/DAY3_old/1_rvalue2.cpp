#include <iostream>

// �ٽ� : value category �� "expression" �� �Ӽ��Դϴ�. 
//		  ��ü�� �Ӽ��� �ƴմϴ�.

// expression(ǥ����) : �ϳ��� ������ �����Ǵ� �ڵ� ����.

int main()
{
	int n = 10;
	 
	n = 10;		// "n" �̶�� ǥ������ lvalue

//	n + 5 = 10;  // "n+5" �̶�� ǥ������ ����� �޸𸮰� �ƴ� "15"��� ��
				// ���� rvalue, error
	
//	n + 2 * 5 = 30; // "n + 2 * 5" �� rvalue, error

	++n = 10;	 // ok... ++n �� lvalue

	n++ = 20; // error.  n++�� rvalue

	int k = 3;
	int s = ++k * ++k; 
	std::cout << s << std::endl; //  25
}
// �������� ����� ���ô�.
int operator++(int& n, int) // �������� �������� ������ ���� 2��° �����ʿ�
{
	int temp = n;
	n = n + 1;
	return temp;
}

// ������ ++�� ���� ����� ���ô�. - ���� int ������ ����� ������..
int& operator++(int& n)
{
	n = n + 1;
	return n;
}