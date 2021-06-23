// 2_thiscall3_1
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
struct Point
{
	int x{ 0 };
	int y{ 0 };
	// <
};
int main()
{
	std::vector<Point> v;
	v.emplace_back(1, 1);
	v.emplace_back(2, 2);
	v.emplace_back(6, 3);
	v.emplace_back(3, 10);

	// 기존 STL : 요소의 크기 비교가 가능해야 sort 할수 있다.
	//std::sort(v.begin(), v.end()); // C++20 이전 스타일
	
	std::sort(v.begin(), v.end(),
		[](const Point& p1, const Point&p2) {return p1.x < p2.x; });

	//std::ranges::sort(v); // C++20 스타일

	std::ranges::sort(v, std::less{}, &Point::x ); // C++20 스타일

}










// Ctrl + F5