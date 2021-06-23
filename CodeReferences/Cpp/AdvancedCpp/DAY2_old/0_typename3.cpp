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
// 생성자 모양 -> List<타입>
List()->List<int>;
//template<typename C> List(const C& c)->List< typename C::value_type >;
template<typename C> List(C&& c)->List< typename std::remove_reference_t<C>::value_type >; // C++17
//template<typename C> List(C&& c)->List< std::ranges::range_value_t<C> >; // C++20


int main()
{
	List<int> s1(10, 3);
	List      s2(10, 3); // C++17 부터는 클래스 템플릿도 템플릿 인자 추론 가능합니다.
	List      s3;

	std::vector<int> v = { 1,2,3 };

	List s4(v);
}

// /std:c++latest