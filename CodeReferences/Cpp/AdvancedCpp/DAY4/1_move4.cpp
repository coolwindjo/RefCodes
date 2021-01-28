#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>  // g++ �� ����� �߰��ϼ���
using namespace std;

// g++ 1_move4.cpp   -fno-elide-constructors

// �ٽ�
// C++98 : �Ѱ��� ���� ������ - "���� ����" �� "�������"����� ����
// C++11 : �ӽð�ü�� ���� ���� �����ڸ� �Ѱ� �� �����ڴ� ��..
//         A. ������ ���� ������
//         B. �ӽð�ü�� ���� ���� ������ - "�ڿ��� �̵�(move)"�� ����
//						=> "move ������"


class Cat
{
	char* name;
	int   age;
public:
	Cat(const char* n, int a) : age(a)
	{
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
	~Cat() { delete[] name; }

	// �Ϲ����� ������ ���� ������
	Cat(const Cat& c)	: age(c.age) 
	{
		name = new char[strlen(c.name) + 1];
		strcpy(name, c.name);
		std::cout << "Copy" << std::endl;
	}
	// �ӽð�ü �϶� ����� ���� ������
	Cat( Cat&& c) : age(c.age), name(c.name)
	{
		// �ݵ�� ���� ��ü�� ���� �����ʹ� 
		// 0���� reset �Ǿ�� �մϴ�.
		c.name = nullptr;
		std::cout << "Move" << std::endl;
	}
};

Cat foo()
{
	Cat c("yaong", 5);
	return c;  // ���⼭ �ӽð�ü�� ���鶧 move ȣ��
}

int main()
{
	Cat c1("nabi", 2);
	Cat c2 = c1; 
	Cat c3 = foo(); // �̶��� �������� ������ ���ô�.
//  Cat c3 = �ӽð�ü;
}	