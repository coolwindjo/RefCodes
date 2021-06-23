#include <iostream>

// trivial : 하는 일이 "자명(널리 알려진 디폴트 방식대로 동작)" 하다는 의미.
// trivial 생성자      : 아무 일도 하지 않은 생성자
// trivial 복사 생성자 : 모든 멤버를 얕은 복사하는 복사 생성자.

class A
{
};

// B의 생성자는 trivial 할까요 ?
class B // : public A
{
//	A a;
public:
	// virtual void foo() {}
};

// 1. 가상함수가 없고
// 2. 기반 클래스가 없거나 기반 클래스의 생성자가 trivial 하고
// 3. 객체형 멤버가 없거나 객체형 멤버의 생성자가 trivial 하고
// 4. 사용자가 만든 생성자가 없을때 
// "생성자는 trivial" 합니다.



int main()
{
	B* p = (B*)malloc(sizeof(B)); // 생성자 호출 안됨.

	// 이미 할당된 메모리에 생성자만 호출하는 문법
	new(p) B; // placement new라고 합니다.

	p->foo();
}