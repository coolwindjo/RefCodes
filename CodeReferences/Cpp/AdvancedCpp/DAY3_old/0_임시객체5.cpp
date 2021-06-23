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
	std::cout << d.value << std::endl; // 20

	// 아래 2줄의 차이점은 뭘까요 ?
	std::cout << static_cast<Base>(d).value << std::endl; // 10
	std::cout << static_cast<Base&>(d).value << std::endl; // 10

	//static_cast<Base>(d).value = 30;// error
	static_cast<Base&>(d).value = 30;// ok
}
// 핵심. 임시객체는
// 1. 사용자가 직접 만들기도 하고 -- 함수 인자로 전달  foo( Point(1,2))
// 2. 사용자가 코드가 실행될때 자동으로생성되기도 합니다.
//   A. 값을 반환하는 함수
//   B. 값 타입 으로 캐스팅.
//    => 결론, 사용자 정의 타입의 경우 되도록 "값 캐스팅"을 사용하지 마세요.





