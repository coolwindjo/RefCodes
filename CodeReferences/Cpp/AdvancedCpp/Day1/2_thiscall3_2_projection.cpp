#include <iostream>
using namespace std;

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

template<typename T>
T max(T a, T b)
{
	return a < b ? b : a;
}

// C++20 �� Ranges library�� algorithm���� �Ʒ�ó�� �����ǰ� �ȴ�.
// �̶� &Point::y �� �����ϴ� ���� "Projection" �̶�� �Ѵ�.
template<typename T, typename T2>
T max(T a, T b, T2 T::*p)
{
	T2 &r1 = a.*p;
	T2 &r2 = b.*p;
	return r1 < r2 ? b : a;
}

int main()
{
	Point pt1;
	Point pt2;
	max(pt1, pt2, &Point::y);

	return 0;
}