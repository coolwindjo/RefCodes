#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

// 클래스가 "포인터를 가지고 자원을 할당하면 3개의 함수가 추가로 필요 합니다."

// Rule Of 3 : 소멸자, 복사 생성자, 대입 연산자  ==> C++98 이야기.

// Rule Of 5 : Move 생성자와 Move 대입연산자를 추가로 제공하면 좋다



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

		std::cout << "복사생성자" << std::endl;
	}
	People& operator=(const People& p)
	{
		if (&p == this) return *this;

		std::cout << "복사 대입연산자" << std::endl;
		age = p.age;

		delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);

		return *this;  
	}
	// move 계열의 함수.
	People(People&& p) : age(p.age), name(p.name)
	{
		p.name = nullptr;
		std::cout << "move 생성자" << std::endl;
	}

	People& operator=(People&& p)
	{
		if (&p == this) return *this;

		std::cout << "move 대입연산자" << std::endl;
		age = p.age;
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




