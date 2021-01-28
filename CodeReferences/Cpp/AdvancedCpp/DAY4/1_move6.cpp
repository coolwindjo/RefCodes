#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

// �ٽ� : move �迭�Լ�(move������, move ���Կ�����)������
//       �ݵ�� ��� ����� move�� �Űܾ� �մϴ�.!!!
//       

class People
{
	char* name;
	int   age;
	std::string addr;
public:
	People(const char* s, int a, std::string addr ) : age(a), addr(addr)
	{
		name = new char[strlen(s) + 1];
		strcpy(name, s);
	}
	~People() { delete[] name; }


	People(const People& p) : age(p.age), addr(p.addr)
	{
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);

		std::cout << "���������" << std::endl;
	}


	People& operator=(const People& p)
	{
		if (&p == this) return *this;

		std::cout << "���� ���Կ�����" << std::endl;
		age = p.age;
		addr = p.addr;

		delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);

		return *this;
	}
	// move �迭�� �Լ�.
	People(People&& p) noexcept ( std::is_nothrow_move_constructible_v<std::string> )
//		: age(p.age), name(p.name), addr(p.addr)  // ���� �̷��� �ϸ� �ȵ˴ϴ�. string �� ���������ȣ��
		: age(p.age), name(p.name), addr(std::move(p.addr)) // ok.. string�� move ������ ȣ��
	{
		p.name = nullptr;
		std::cout << "move ������" << std::endl;
	}

	People& operator=(People&& p) noexcept( std::is_nothrow_move_assignable_v<std::string>  )
	{
		if (&p == this) return *this;

		std::cout << "move ���Կ�����" << std::endl;
		age = p.age;
		addr = std::move(p.addr);
		delete[] name;

		name = p.name;
		p.name = nullptr;

		return *this;
	}


};



int main()
{
	People p1("kim", 20);
	People p2 = p1;
	p2 = p1;

	People p3 = std::move(p1);
	p3 = std::move(p2);
}




