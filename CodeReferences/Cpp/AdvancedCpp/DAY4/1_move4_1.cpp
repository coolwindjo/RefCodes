// 1_move4_1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>  // g++ �� ����� �߰��ϼ���
using namespace std;

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
	Cat(const Cat& c) : age(c.age)
	{
		name = new char[strlen(c.name) + 1];
		strcpy(name, c.name);
		std::cout << "Copy" << std::endl;
	}
	// move �����ڰ� ���ٸ�!!
	/*
	Cat(Cat&& c) : age(c.age), name(c.name)
	{
		c.name = nullptr;
		std::cout << "Move" << std::endl;
	}
	*/
};

Cat foo()
{
	Cat c("yaong", 5);
	return c; 
}

int main()
{
	Cat c1("nabi", 2);
	Cat c2 = c1;		// ����
	Cat c3 = foo();		// move

	Cat c4 = static_cast<Cat&&>(c1); // ���� �����ڰ� �ƴ� move �����ڸ� ȣ���� �޶�� �ǹ�.
	Cat c5 = std::move(c2);          // �� �Լ��� �ϴ����� ��ó�� ĳ�����ϴ� ���� �մϴ�.
}

// �ٽ� 
// 1. �ᱹ �ڿ��� �ű�� ���� "Cat Ŭ����"�� ���� ����� ������ "move������" �Դϴ�.
// 2. std::move() �� ����, move �����ڸ� ȣ���ϱ� ���� ĳ���� �Ѱ��� �Ұ� �մϴ�.

// Ŭ���� �����
// ==> �ڽ��� ����ϴ� Ŭ������ "move�����ڰ� �ִ��� ������" ����� �ʿ� ����..
//     �ʿ��� ������ ������ "std::move()" ����ص� �˴ϴ�.


// Ŭ���� ������
// ==> move �����ڴ� �ݵ�� ���� �ʿ�� ����.! ������ ���� ������ ���
//     ��, move �����ڸ� �����ϸ� ���� ���� �ִ�.

// STL �� string, vector, list ���� ��� Ŭ������ �̹� "move �����ڸ� ���� �ϰ� �ֽ��ϴ�."



