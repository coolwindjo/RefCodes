// 4_FUNCTOR1
#include <iostream>

// 함수 객체(Function Object, Functor )
// () 연산자를 재정의 해서 함수 처럼 사용가능한 객체
// "상태와 동작"을 가지는 함수!!
// 요즘에는 "함수객체"라는 용어 대신 "callable object"

// callable object  : () 로 호출 가능한 모든것, - 함수, 함수객체, 람다표현식

class URandom
{
	int history[10];
public:
	void reset_history() {}
	int operator()()
	{
		// 멤버 데이타를 통해서 상태를 관리
		return rand() % 10;
	}
};

int main()
{
	URandom urand; 
	urand(); // 함수 처럼 사용할수 있게 하려면
			 // urand.operator()() 가 되면 됩니다.
			 // urand.next()

	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}