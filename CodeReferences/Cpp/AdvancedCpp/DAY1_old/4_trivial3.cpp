#include <iostream>
#include <type_traits>

struct Point
{
	int x, y;

	Point() = default;
	Point(int a, int b) : x(a), y(b) {}

//	Point(const Point& pt) : x(pt.x), y(pt.y) {}
//	Point(const Point& pt) = default;
};

// ��� : �� �Լ��� trivial ���θ� �����ؼ� ����ȭ�� �˰����� �����ϴ� �ڵ尡
//        �θ� ���˴ϴ�.

//   �̷� ����� C++20 ������ "Concept" ���� ź��..

template<typename T> void copy(T* dst, T* src, std::size_t size)
{
	if (std::is_trivially_copy_constructible_v<T>)
	{
		std::cout << "��������ڰ� �ϴ����� ���� ���" << std::endl;
		memcpy(dst, src, sizeof(T)* size);
	}
	else
	{
		std::cout << "��������ڰ� �ϴ����� �ִ� ���" << std::endl;

		// ��� ��ҿ� �ؼ� "���������"�� ȣ���ؼ� �ű��.
		while (size--)
		{
			new(dst) T(*src); // ���� ������ ȣ��
							// std::construct_at()..
			++dst, ++src;
		}
	}
}
int main()
{
	Point pt1[5] = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5} };
	Point pt2[5];

	copy(pt2, pt1, 5);

}