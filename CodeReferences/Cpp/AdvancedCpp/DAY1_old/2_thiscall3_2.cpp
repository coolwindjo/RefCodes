#include <iostream>

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

// 아래 버전은 T 자체에 대해서 < 연산수행.
template<typename T> T Max(T a, T b)
{
	return a < b ? b : a;
}
// C++20 의 Ranges 라이브러이의 알고리즘들이 아래 처럼 구현되게 됩니다.
// 이때 &Point::y 를 전달하는 것을 "Projection" 이라고 합니다.
template<typename T, typename T2> T Max(T a, T b, T2 T::*p )
{
	// T  : Point
	// T2 : int

	T2& r1 = a.*p;
	T2& r2 = b.*p;

	return r1 < r2 ? b : a;
}

int main()
{
	Point p1;
	Point p2;
	Max(p1, p2, &Point::y);
}