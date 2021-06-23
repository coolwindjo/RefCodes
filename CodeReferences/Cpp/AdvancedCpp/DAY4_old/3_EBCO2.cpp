#include <iostream>

class Empty
{
};
// 핵심 : Empty 를 멤버로 놓으면 크기가 1로 계산되지만(Padding 포함시 4)
//		  Empty 로 부터 상속받으면 크기가 0으로 계산됩니다.
//		 Empty Base Class Optimization (EBCO)라는 이름을 가진 기술

struct Data
{
	Empty e;
	int   n;
};
struct Data2 : public Empty
{
	int   n;
};


int main()
{
	Data d;
	std::cout << sizeof(d) << std::endl;  // 8

	std::cout << sizeof(Data2) << std::endl; // 4
}





