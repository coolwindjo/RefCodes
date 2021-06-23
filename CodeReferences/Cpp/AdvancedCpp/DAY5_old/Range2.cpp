// RANGE1
#include <iostream>
#include <vector>
#include <ranges>

template<typename T> class take_view
{
	T& con;	  // 실제 C++ 표준은 ref_view<T> 라는 기술 사용합니다.
	int count = 0;
public:
	take_view(T& c, int n) : con(c), count(n) {}

	auto begin() const { return con.begin() ;	}
	auto end()   const { return std::next(con.begin(), count); }
};

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	// v의 앞에서 부터 3개까지 접근 가능한 range 객체 생성
	// range : 시작과 끝을 가진 반복자 한쌍..
	auto r = v | std::views::take(3);

	// 위 한줄은 아래와 완전히 동일
	//std::ranges::take_view tv(v, 3);
	v[0] = 110;
	take_view tv(v, 3);

	for (auto n : tv) std::cout << n << std::endl;

	std::sort(v.begin(), v.end()); // 기존의 STL 스타일

	std::ranges::sort(v);          // ranges 라이브러리 스타일
	
}