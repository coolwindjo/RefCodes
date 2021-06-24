#include <iostream>
#include <type_traits>	// C++11 의 type traits Library
						// Type에 대한 다양한 정보를 조사

// 핵심 1. Trivial 여부 조사방법

class A
{

};

class Test
	: public A
{
	/*/
	int a = 10;	// 이 초기화 Code 때문에 Compiler 가 만든 Default 생성자는 non-trivial!
	/*/
	int a;
	//*/
public:
	// virtual
	void foo() {}

	/*/
	Test() {}	// 구현에 아무 내용도 없지만, Compiler는 생성자가 하는일이 있다고 가정함
				// => Trivial 하지 않음!
	/*/
	Test() = default;	// C++11의 새로운 문법
						// 인자없는 (Default) 생성자를 만들어 달라는 의미
						// Test(): a(10) {}
	Test(int a, int b) {}
	//*/
};

int main()
{
	bool b = std::is_trivially_default_constructible_v<Test>;

	std::cout << std::boolalpha << b << std::endl;
}