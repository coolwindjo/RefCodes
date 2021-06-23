#include <iostream>

// 생성자 호출순서
// 1. 기반 클래스의 멤버의 생성자
// 2. 기반 클래스의 생성자
// 3. 자신의 멤버의 생성자
// 4. 자신의 생성자..

// BaseMember
struct BM	
{
	BM()  { std::cout << "BM()" << std::endl; }
	~BM() { std::cout << "~BM()" << std::endl; }
};
struct DM // DerivedMember
{
	DM() { std::cout << "DM()" << std::endl; }
	~DM() { std::cout << "~DM()" << std::endl; }
};
struct Base
{
	BM bm;
	Base() //   Base() : bm() 
	{
		std::cout << "Base()" << std::endl; 
	}
	~Base() { std::cout << "~Base()" << std::endl; }
};
struct Derived : public Base
{
	DM dm;
	// 아래 코드를 컴파일러가 주석처럼 변경합니다.
	Derived() // Derived() : Base(), dm()
	{
		std::cout << "Derived()" << std::endl; 
	}
	~Derived() { std::cout << "~Derived()" << std::endl; }
};

int main()
{
	Derived d; // 이 순간의 결과를 예측해 보세요.
}
