// 1_move4_1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>  // g++ 은 이헤더 추가하세요
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
	// move 생성자가 없다면!!
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
	Cat c2 = c1;		// 복사
	Cat c3 = foo();		// move

	Cat c4 = static_cast<Cat&&>(c1); // 복사 생성자가 아닌 move 생성자를 호출해 달라는 의미.
	Cat c5 = std::move(c2);          // 이 함수가 하는일이 위처럼 캐스팅하는 일을 합니다.
}

// 핵심 
// 1. 결국 자원을 옮기는 것은 "Cat 클래스"를 만든 사람이 제공한 "move생성자" 입니다.
// 2. std::move() 는 단지, move 생성자를 호출하기 위해 캐스팅 한것이 불과 합니다.

// 클래스 사용자
// ==> 자신이 사용하는 클래스가 "move생성자가 있는지 없는지" 고려할 필요 없이..
//     필요한 곳에서 무조건 "std::move()" 사용해도 됩니다.


// 클래스 제작자
// ==> move 생성자는 반드시 만들 필요는 없다.! 없으면 복사 생성자 사용
//     단, move 생성자를 제공하면 빨라 질수 있다.

// STL 의 string, vector, list 등의 모든 클래스는 이미 "move 생성자를 지원 하고 있습니다."



