// 4_FUNCTOR1
#include <iostream>

// 핵심 : 일반 함수는 "동작은 있지만 상태를 가질수 없다"

// 0 ~ 9 사이의 "중복되지 않은" 난수를 반환하는 함수
int urand()
{
	return rand() % 10;
}

int main()
{
	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}