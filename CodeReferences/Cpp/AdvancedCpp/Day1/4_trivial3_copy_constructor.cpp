#include <iostream>
#include <cstring>
#include <type_traits>

struct Point
{
	int x, y;

	Point() = default;
	Point(int a, int b) : x(a), y(b) {}

	/*/
	Point(const Point &pt) : x(pt.x), y(pt.y) {}
	/*/
	Point(const Point &pt) = default;
	//*/
};

// 핵심 1. 각 함수의 trivial 여부를 조사해서 최적화된 Algorithm을 구현하는 Code가 널리 사용된다.
// 			=> C++20 "Concept" 문법 탄생
template<typename T>
void copy(T* dst, T* src, std::size_t size)
{
	if (std::is_trivially_copy_constructible_v<T>) {
		std::cout << "Trivial Copy Constructor" <<std::endl;
		memcpy(dst, src, sizeof(T) * size);
	}
	else{
		std::cout << "Non-trivial Copy Constructor" <<std::endl;
		// 모든  Element에 대해서 "Copy Constructor" 를 호출해서 옮긴다.
		while(size--){
			new(dst) T(*src);	// Calling Copy Constructor...
								// std::construct_at()...
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