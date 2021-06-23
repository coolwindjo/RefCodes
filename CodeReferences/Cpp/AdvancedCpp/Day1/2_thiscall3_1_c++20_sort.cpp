#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

int main()
{
	vector<Point> vp;
	vp.emplace_back(1, 1);
	vp.emplace_back(2, 2);
	vp.emplace_back(6, 3);
	vp.emplace_back(3, 10);

	// 기존 STL: 요소의 크기 비교가 가능해야 sort 할 수 있다.
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;
	sort(vp.begin(), vp.end(),
		[](const Point &a, const Point &b){return a.y<b.y;});	// C++20 이전 스타일

	// ranges::sort(vp);	// C++20 Style
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;

	ranges::sort(vp, less{}, &Point::x);	// C++20 Style
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;

	return 0;
}