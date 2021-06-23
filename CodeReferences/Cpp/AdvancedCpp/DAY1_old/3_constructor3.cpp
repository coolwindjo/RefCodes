#include <iostream>

// 생성자와 가상함수
// 핵심 1. 생성자 안에서는 가상함수가 동작하지 않습니다.
//			항상 자신의 멤버를 호출하게 됩니다.
// 왜 이렇게 설계 했을까요 ? 언어 설계자를 생각해 보세요..
struct Base
{
	Base() { goo(); } // Base::goo
					// Derived::goo 를 호출했다면 초기화 되지 않은 멤버 데이타(x)를
					// 사용하게 됩니다.
	
	void foo() { } //goo(); // 2

	virtual void goo() { std::cout << "Base::goo" << std::endl; }     // 1
};

struct Derived : public Base
{
	int x = 10; // C++ : 이 초기화 보다 기반 클래스 생성자가 먼저 호출
			    // C# : 기반 클래스 생성자 보다 이 초기화가 먼저 수행.
	Derived() : x(10) {} // Derived() : Base(), x(10) {}

	virtual void goo() override { std::cout << "Derived::goo : " << x << std::endl; } // 2
};

int main()
{
	Derived d;
	d.foo();   // 결과 예측해 보세요
}

