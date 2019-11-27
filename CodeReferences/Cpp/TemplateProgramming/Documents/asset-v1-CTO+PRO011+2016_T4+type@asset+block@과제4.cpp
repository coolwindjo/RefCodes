#include <iostream>
using namespace std;

// 과제 4. 
// 출제 의도 : 가변인자 템플릿을 활용


// 아래 코드는 C++ 창시자인 stroustrup 의 홈페이지에 있는 코드입니다.

// 아래 링크를 참고 하세요..
// http://www.stroustrup.com/C++11FAQ.html#variadic-templates



void cpp_print(const char* s)
{
	while (s && *s) {
		if (*s == '%' && *++s != '%')											
			throw runtime_error("invalid format: missing arguments");
		std::cout << *s++;
	}
}

template<typename T, typename... Args>		
void cpp_print(const char* s, T value, Args... args)
{
	while (s && *s) {
		if (*s == '%' && *++s != '%') {	
			std::cout << value;		
			return cpp_print(++s, args...); 
		}
		std::cout << *s++;
	}
	throw std::runtime_error("extra arguments provided to printf");
}

int main()
{
	try
	{
		//cpp_print("%d");

		cpp_print("%d\n", 1, 2, 3);
		
		//cpp_print("%d\n", 1);
	}
	catch (...)
	{
		cout << "exception.." << endl;
	}
}