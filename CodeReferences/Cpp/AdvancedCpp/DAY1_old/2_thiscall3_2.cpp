#include <iostream>

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

// �Ʒ� ������ T ��ü�� ���ؼ� < �������.
template<typename T> T Max(T a, T b)
{
	return a < b ? b : a;
}
// C++20 �� Ranges ���̺귯���� �˰������ �Ʒ� ó�� �����ǰ� �˴ϴ�.
// �̶� &Point::y �� �����ϴ� ���� "Projection" �̶�� �մϴ�.
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