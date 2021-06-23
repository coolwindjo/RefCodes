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

	// ���� STL: ����� ũ�� �񱳰� �����ؾ� sort �� �� �ִ�.
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;
	sort(vp.begin(), vp.end(),
		[](const Point &a, const Point &b){return a.y<b.y;});	// C++20 ���� ��Ÿ��

	// ranges::sort(vp);	// C++20 Style
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;

	ranges::sort(vp, less{}, &Point::x);	// C++20 Style
	for (auto pt : vp){cout << "[" << pt.x << "," << pt.y << "] ";}
	cout <<endl;

	return 0;
}