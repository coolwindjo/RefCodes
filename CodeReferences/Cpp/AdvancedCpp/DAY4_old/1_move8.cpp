#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

// rule of 0 : 자원을 직접 관리하지 말고 자원 관리 클래스를 사용해라
//			문자열이 필요 하면 char* => string
//			int* => vector 또는 smart pointer
//			
class People
{
	std::string name;
	int   age;
	std::string addr;
public:
	People(std::string name, int a, std::string addr) : name(name), age(a), addr(addr)
	{
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




