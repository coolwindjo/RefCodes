#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <bits/stdc++.h>
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

	// ?? ??? ??? ?? ???
	Cat(const Cat& c)
		: age(c.age)
	{
		name = new char[strlen(c.name) + 1];
		strcpy(name, c.name);
	}
};
int main()
{
	Cat c1("nabi", 2);
	Cat c2 = c1; // runtime error. 얕은 복사 문제.
}