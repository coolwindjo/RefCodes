#include <iostream>
#include <algorithm>
#include <vector>

// �����̳�::value_type     => �����̳ʰ� �����ϴ� Ÿ��
// �ݺ���Ÿ��::value_type   => �ݺ��ڰ� ����Ű�� Ÿ��

// std::iter_value_t<�ݺ���Ÿ��> => �ݺ��ڰ� ����Ű�� Ÿ��(C++20, ��¥ �����͵� ����)

//template<typename Iter, typename T > requires std::predicate<T, typename Iter::value_type >
//template<typename Iter, typename T > requires std::predicate<T, typename std::iterator_traits<Iter>::value_type >

template<typename Iter, typename T > requires std::predicate<T, std::iter_value_t<Iter> >
void find(Iter first, Iter last, T value)
{
	std::cout << "���� �˻�" << std::endl;
}

template<typename Iter, typename T > requires (!std::predicate < T, std::iter_value_t<Iter> >)
void find(Iter first, Iter last, T value)
{
	std::cout << "�� �˻�" << std::endl;
}

int main()
{
//	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	int v[10] = { 1,2,3,4,5,6,7,8,9,10 };

//	auto p1 = std::find(   v.begin(), v.end(), 3);
//	auto p2 = std::find_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; } );

//	find(v.begin(), v.end(), 3);
//	find(v.begin(), v.end(), [](int n) { return n % 2 == 0; });

	// v.begin() ���� std::begin(v) �� �����ϴ�.
	// v�� raw �迭�̶� ���� ���� �����մϴ�.
	find(std::begin(v), std::end(v), 3);
	find(std::begin(v), std::end(v), [](int n) { return n % 2 == 0; });


}

