#include <iostream>

class Test;		// 클래스 전방 선언..
				// 완전한 선언이 없어도, 포인터 타입은 사용가능

				// 불완전한 타입(incomplete type )
				// incompete 타입은 delete 시에 소멸자가 호출되지 않는다.
// Test* p; // ok
// Test  t; // error. 완전한 선언 필요

// "checked delete" 개념
void foo(Test* p)
{
//	enum { type_must_be_complete = sizeof(Test) }; // 최적화를 방지하기 위해 sizeof
												   // 반환값 받기

	// C++11 이후 스타일
	static_assert(sizeof(Test) > 0, "delete incomplete type");

	delete p;
}



class Test
{
public:
	Test()  { std::cout << "Test()" << std::endl; }
	~Test() { std::cout << "~Test()" << std::endl; }
};

int main()
{
	Test* p = new Test;
	foo(p);
}
