#include <vector>
#include <type_traits>
template<typename T> class List
{
public:
	List() {}
	List(std::size_t sz, T value) {}

	//template<typename C> List(const C& c) {}
	template<typename C> List(C&& c) {}
};
// class template type deduction guide
// ������ ��� -> List<Ÿ��>
List()->List<int>;
//template<typename C> List(const C& c)->List< typename C::value_type >;
template<typename C> List(C&& c)->List< typename std::remove_reference_t<C>::value_type >; // C++17
//template<typename C> List(C&& c)->List< std::ranges::range_value_t<C> >; // C++20


int main()
{
	List<int> s1(10, 3);
	List      s2(10, 3); // C++17 ���ʹ� Ŭ���� ���ø��� ���ø� ���� �߷� �����մϴ�.
	List      s3;

	std::vector<int> v = { 1,2,3 };

	List s4(v);
}

// /std:c++latest