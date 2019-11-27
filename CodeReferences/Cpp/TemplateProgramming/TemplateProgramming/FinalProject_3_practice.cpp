#include <iostream>
#include <vector>
#include <array>
#include <type_traits>

using namespace std;

/*
template<typename T, size_t(T::*)() const> struct SFINAE {};
template<typename T> char check(SFINAE<T, &T::resize>*);
/*/
template<typename T> char check(decltype(&T::resize));
//*/
template<typename T> short check(...);

struct dummy{};

template <typename C, typename P>
static auto test(P * p) -> decltype(std::declval<C>().resize(*p), std::true_type());

template <typename, typename>
static std::false_type test(...);

template<typename T> 
struct has_resize
{
	//enum { value = (sizeof(check<T>(0)) == sizeof(char)) };
	//static constexpr int value = (sizeof(check<T>(0)) == sizeof(char));
	typedef decltype(test<T, dummy>(nullptr)) type;
	static constexpr bool value = std::is_same<std::true_type, decltype(test<T, dummy>(nullptr))>::value;
};

template<typename T> void foo(T& c)
{
	if (has_resize<T>::value)
		cout << "T has resize" << endl;
	else
		cout << "T does not have resize" << endl;
}

int main()
{
	vector<int> v = { 1,2,3,4,5 };
	array<int, 10> ar = { 1,2,3,4,5 };
	v.resize(3);
	foo(v); // vector는 resize 함수를 가지고 있습니다.
	foo(ar); // array 는 resize 함수가 없습니다.

	system("pause");
	return 0;
}