#include <iostream>
#include <string>
#include <vector>

// 왜 move가 중요한가 ? 
// Algorithm 작성시 "복사" 보다는 "move" 가
// 빠른 경우가 많습니다.

// 적절한 move의 사용은 Program 성능을 향상 시킬 수 있습니다.

// move: 결국 주소를 옮기는 개념
// 그런데, 주소를 옮기는 것을 모든 Type에 적용하는 "일반적인 문법"의 탄생!

// 아래 Swap은 복사 기반의 함수 입니다.
// // template<typename T>
// // void Swap(T& a, T& b)
// // {
// // 	T tmp = a;
// // 	a = b;
// // 	b = tmp;
// }

template<typename T>
void Swap(T& a, T& b)
{
	T tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
}

int main()
{
	std::string s1 = "hello";
	std::string s2 = "world";
	Swap(s1, s2);
}



