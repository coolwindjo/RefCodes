// 10_EBCO -  73 page
#include <iostream>

// Empty Class : non static 멤버 데이타가 없는 클래스, 가상함수가 없어야 한다.
//					크기가 1이다.

// 함수 객체,
// 캡쳐하지 않은 람다표현식들이 전부 empty 클래스 입니다.

class Empty 
{
	static int cnt;
public:
	void foo() {}
};
int Empty::cnt = 0;

struct Plus
{
	int operator()(int a, int b) { return a + b; }
};

int main()
{
	Empty e;
	std::cout << sizeof(e) << std::endl; // 1
}





