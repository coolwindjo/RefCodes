#include <iostream>
struct Base
{
	int value = 10; 
};
struct Derived : public Base
{
	int value = 20;
};
int main()
{
	Derived d;
	std::cout << d.value << std::endl; 	// 20

	// 아래 2 줄의 차이점은 뭘까요?
	std::cout << static_cast<Base>(d).value << std::endl; 	// 10: Base의 임시객체를 만들어 그 Member를 보여줌
	std::cout << static_cast<Base&>(d).value << std::endl; 	// 10

	// static_cast<Base>(d).value = 30; // Error.
	static_cast<Base&>(d).value = 30; // OK
}
// 핵심. 임시 객체는 
// 1. 사용자가 직접 만들기도 하고, (함수 인자로 전달)
// 2. 사용자가 Code가 실행될 때 자동으로 생성되기도 합니다.
//	A. 값을 반환하는 함수
//	B. 값 Type 으로 Casting
//		=> 결론, 사용자 정의 Type의 경우, 가능한한 "값 Casting"은 사용하지 말아야 함

