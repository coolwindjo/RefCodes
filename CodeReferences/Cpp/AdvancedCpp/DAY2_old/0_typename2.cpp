#include <iostream>
#include <vector>
#include <ranges> // C++20
#include <list>
// �ٽ� : typename �����̳�::value_type   => �����̳ʰ� �����ϴ� Ÿ���� �ʿ��Ҷ� ���

/*
void print_first_element(std::vector<int>& v)
{
	int n = v.front();
	std::cout << n << std::endl;
}
*/
/*
template<typename T>
void print_first_element(std::vector<T>& v)
{
	T n = v.front();
	std::cout << n << std::endl;
}
*/
template<typename T>
void print_first_element( T& v)
{
	// ?�� ������ ������.
	// T : list<double>
	// T::value_type   => list<double>::value_type  => double

	// raw array �� �����ϸ� T : int[10] �� ����Դϴ�.
	// int[10]::value_type �� �ɼ� �����Ƿ� error

	typename T::value_type n = v.front(); // C++98
							 

	std::ranges::range_value_t<T> n = std::front(v); //  C++20 ���� ����˴ϴ�.

	std::cout << n << std::endl;
}
int main()
{
//	std::vector<int>    v = { 1,2,3,4,5,6,7,8,9,10 };
//	std::vector<double> v = { 1,2,3,4,5,6,7,8,9,10 };
//	std::list<double> v = { 1,2,3,4,5,6,7,8,9,10 };
	int v[10] = { 1,2,3,4,5,6,7,8,9,10 };

	print_first_element(v);
}

// STL �� ����
// �����̳ʰ� �����ϴ� Ÿ���� �˰� �������� �־���.
/*
template<typename T> class list
{
public:
	typedef T value_type; // STL�� ���� �ٽ�.
};
list<int> s = { 1,2,3 };
list<int>::value_type n = s.front(); // int n = s.front()
*/




