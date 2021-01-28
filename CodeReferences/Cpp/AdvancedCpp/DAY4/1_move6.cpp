#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

// 핵심 : move 계열함수(move생성자, move 대입연산자)에서는
//       반드시 모든 멤버를 move로 옮겨야 합니다.!!!
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

		std::cout << "복사생성자" << std::endl;
	}


	People& operator=(const People& p)
	{
		if (&p == this) return *this;

		std::cout << "복사 대입연산자" << std::endl;
		age = p.age;
		addr = p.addr;

		delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);

		return *this;
	}
	// move 계열의 함수.
	People(People&& p) noexcept ( std::is_nothrow_move_constructible_v<std::string> )
//		: age(p.age), name(p.name), addr(p.addr)  // 절대 이렇게 하면 안됩니다. string 의 복사생성자호출
		: age(p.age), name(p.name), addr(std::move(p.addr)) // ok.. string의 move 생성자 호출
	{
		p.name = nullptr;
		std::cout << "move 생성자" << std::endl;
	}

	People& operator=(People&& p) noexcept( std::is_nothrow_move_assignable_v<std::string>  )
	{
		if (&p == this) return *this;

		std::cout << "move 대입연산자" << std::endl;
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




