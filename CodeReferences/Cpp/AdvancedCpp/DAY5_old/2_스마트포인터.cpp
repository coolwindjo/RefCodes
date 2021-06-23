#include <iostream>

class Car
{
public:
	void Go() { std::cout << "Go" << std::endl; }
	~Car()    { std::cout << "~Car" << std::endl; }
};
// 개념 : 객체가 다른 타입의 포인터 처럼 사용되는 것
// 구현원리 : -> 연산자와 * 연산자를 재정의 해서 포인터 처럼 보이게 하는 것.
// 장점 : 객체이므로 생성/복사/대입/소멸의 모든 과정을 제어할수 있다.
//			특히, 소멸자에서 자동 삭제 기능..
// 핵심은 아래 클래스 입니다.
class Ptr
{
	Car* obj;
public:
	Ptr(Car* p = 0) : obj(p) {}
	~Ptr() { delete obj; }
	Car* operator->() { return obj; }
	Car& operator*() { return *obj; }
};

int main()
{
	Ptr p = new Car;  // Ptr p( new Car )

	p->Go(); // p.operator->() Go() 인데
			// (p.operator->())->Go() 처럼 해석됩니다.
			// 1000->Go()
	(*p).Go();
}


