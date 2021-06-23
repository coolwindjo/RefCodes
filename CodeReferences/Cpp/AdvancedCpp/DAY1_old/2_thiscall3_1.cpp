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

	// ���� STL : ����� ũ�� �񱳰� �����ؾ� sort �Ҽ� �ִ�.
	//std::sort(v.begin(), v.end()); // C++20 ���� ��Ÿ��
	
	std::sort(v.begin(), v.end(),
		[](const Point& p1, const Point&p2) {return p1.x < p2.x; });

	//std::ranges::sort(v); // C++20 ��Ÿ��

	std::ranges::sort(v, std::less{}, &Point::x ); // C++20 ��Ÿ��

}










// Ctrl + F5