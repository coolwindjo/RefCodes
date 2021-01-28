// RANGE1
#include <iostream>
#include <vector>
#include <ranges>

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
						// 1, 100
	auto r = v | std::views::filter([](int n) { return n % 2 == 0; }) | std::views::take(3);

	v[1] = 100;

	// 위의 명령은 모두 아래처럼 열거할때 동작합니다. - 지연된 실행
	for (auto n : r)
		std::cout << n << std::endl;
}