#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

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

	Cat(const Cat& c)
		: age(c.age)
	{
		name = new char[strlen(c.name) + 1];
		strcpy(name, c.name);
		std::cout<< "copy" <<std::endl;
	}

	Cat(Cat&& c)
		: age(c.age)
		, name(c.name)
	{
		c.name = nullptr;
		std::cout<< "move" <<std::endl;
	}
};

Cat foo()
{
	Cat c("yaong", 5);
	return c;
}

int main()
{
	Cat c1("nabi", 2);
	Cat c2 = c1;	// copy
	Cat c3 = foo();	// move

	Cat c4 = c1;	// copy
	Cat c5 = c2;	// copy

}