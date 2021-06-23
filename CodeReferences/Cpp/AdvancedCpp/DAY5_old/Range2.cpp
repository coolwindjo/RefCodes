// RANGE1
#include <iostream>
#include <vector>
#include <ranges>

template<typename T> class take_view
{
	T& con;	  // ���� C++ ǥ���� ref_view<T> ��� ��� ����մϴ�.
	int count = 0;
public:
	take_view(T& c, int n) : con(c), count(n) {}

	auto begin() const { return con.begin() ;	}
	auto end()   const { return std::next(con.begin(), count); }
};

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	// v�� �տ��� ���� 3������ ���� ������ range ��ü ����
	// range : ���۰� ���� ���� �ݺ��� �ѽ�..
	auto r = v | std::views::take(3);

	// �� ������ �Ʒ��� ������ ����
	//std::ranges::take_view tv(v, 3);
	v[0] = 110;
	take_view tv(v, 3);

	for (auto n : tv) std::cout << n << std::endl;

	std::sort(v.begin(), v.end()); // ������ STL ��Ÿ��

	std::ranges::sort(v);          // ranges ���̺귯�� ��Ÿ��
	
}