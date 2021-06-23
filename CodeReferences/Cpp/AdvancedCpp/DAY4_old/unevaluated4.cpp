#include <iostream>

class Test 
{
public:
//	void resize() {}
};

// 핵심 : SFINAE 기술로 "조건을 만족하지 않으면 실패" 하는 함수 템플릿 설계
//		resize() 함수가 있는지 조사가 필요 

// 아래 템플릿은 T 안에 resize()가 있으면 성공, 없으면 (치환)실패 입니다.
template<typename T> 
int  check( decltype( T().resize() )* p );
		 

template<typename T> char check(...);

int main()
{
	int n = sizeof( check<Test>(0) );

	std::cout << n << std::endl;
}



