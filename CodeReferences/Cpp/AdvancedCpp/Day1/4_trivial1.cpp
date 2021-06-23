#include <iostream>

// trivial: 하는 일이 "자명(Default 동작을 수행)" 하다는 의미
// trivial 생성자		: 아무 일도 하지 않는 생성자
// trivial 복사 생성자	: 모든 Member를 얕은 복사하는 복사 생성자
class A
{
};

// B의 생성자는 trivial 할까? => Nop: Virtual Function Table 을 만든다.
// Trivial Constructor 조건
// 1. No Vitual Function
// 2. No Base Class or Base Class with TRIVIAL constructor
// 3. No Member Attribute Object or Member Attribute Object with TRIVIAL constructor
// 4. No User-defined Constructor
class B
	: public A	// 2.
{
	A a;	// 3.
	int x=10;
public:
	// B(){}	// 4.
	virtual	// 1.
	void foo() { std::cout << x <<std::endl;}
};

int main()
{
	B* p = (B*)malloc(sizeof(B));	// 생성자 호출 안됨
	
	// 이미 할당된 Memory에 생성자만 호출하는 문법 => trivial constructor 아닐때 해결방법
	new(p) B;	// "Placement new" 라고 한다.

	p->foo();
	return 0;
}