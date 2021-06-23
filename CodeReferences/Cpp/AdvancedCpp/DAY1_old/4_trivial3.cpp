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

// 결론 : 각 함수의 trivial 여부를 조사해서 최적화된 알고리즘을 구현하는 코드가
//        널리 사용됩니다.

//   이런 기술이 C++20 에서는 "Concept" 문법 탄생..

template<typename T> void copy(T* dst, T* src, std::size_t size)
{
	if (std::is_trivially_copy_constructible_v<T>)
	{
		std::cout << "복사생성자가 하는일이 없는 경우" << std::endl;
		memcpy(dst, src, sizeof(T)* size);
	}
	else
	{
		std::cout << "복사생성자가 하는일이 있는 경우" << std::endl;

		// 모든 요소에 해서 "복사생성자"를 호출해서 옮긴다.
		while (size--)
		{
			new(dst) T(*src); // 복사 생성자 호출
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