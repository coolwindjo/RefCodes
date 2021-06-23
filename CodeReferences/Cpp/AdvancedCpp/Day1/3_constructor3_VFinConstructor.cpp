#include <iostream>

// 생성자와 가상함수
// 핵심 1. Constructor 안에서 Virtual Function은 동작하지 않는다.
//			=> 항상 자신의 Member Method를 호출하게 된다.
// 			왜그럴깡? 언어 설계자의 입장에서 생각해보면...
//					
struct Base
{
	// /*/
	Base() { goo(); }	// Base::goo
						// Derived::goo 를 호출했다면,
						// 초기화 되지 않은 Member attribute (x)를 사용하게 된다.
	void foo() { }
	/*/
	Base() {}
	void foo() { goo(); }
	//*/
	virtual void goo() { std::cout << "Base::goo" << std::endl; }
};

struct Derived : public Base
{
	int x = 10;	// C++: x=10보다 Base() 가 먼저 호출
				// C#: Base()가 먼저 호출	따라서, 이러한 문법이 추천됨
	Derived() : x(10) {}	// Derived(): Base(), x(10) {}

	virtual void goo() override { std::cout << "Derived::goo" << x << std::endl; }
};

int main()
{
	Derived d;
	d.foo();	// Derived::goo
}