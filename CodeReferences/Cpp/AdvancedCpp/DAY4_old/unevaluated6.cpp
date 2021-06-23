#include <iostream>

class Test
{
public:
	Test(int a) {}
	void resize() {}
};

template<typename T> int  check(decltype(std::declval<T>().resize())* p);
template<typename T> char check(...);

template<typename T> struct has_resize_function
{
	static constexpr bool value = (  sizeof(check<T>(0)) == sizeof(int) );
};

int main()
{
	bool b = has_resize_function<Test>::value;

	std::cout << b << std::endl;
}
// 이 기술의 이름이 "member detect" 라는 C++ Idioms 입니다.


