#include <iostream>
#include <functional>

// 핵심 결론. 완벽한 전달 코드는 대부분
// 1. 반환 Type이 decltyp(auto) 인 경우가 많습니다.
// 2. 인자를 받을 때는 T&& ... args 형태입니다.
// 3. 다른 곳에 인자를 보낼 때는 std::forward<T>(args)... 로 묶어서 전달

class Test
{
private:
	
public:
	Test(/* args */) {}
	~Test() {}
	void foo(int a, int b) {}

};

template<typename F, typename ... T>
decltype(auto) chronometry(F f, T&& ... arg)
{
	// return f( std::forward<T>(arg)... );	// (obj.*f)(10, 20)
	return std::invoke(f, std::forward<T>(arg)...);	// C++17
}

int main()
{
	Test t;
	// int& ret = chronometry( &Test::foo, &t, 10, 20);	// t.foo(10, 20)
	chronometry( &Test::foo, &t, 10, 20);	// t.foo(10, 20)

	return 0;
}
