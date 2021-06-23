#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class People
{
	char* name;
	int   age;
public:
	People(const char* s, int a) : age(a)
	{
		name = new char[strlen(s) + 1];
		strcpy(name, s);
	}
	~People() { delete[] name; }

	People(const People& p) : age(p.age)
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

		delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);

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




