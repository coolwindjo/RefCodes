// 9_완벽한전달_주의사항
#include <iostream>

template<typename F, typename T>
void chronometry(F f, T&& arg)
{
	f(std::forward<T>(arg));
}
void foo() {}
void foo(int a) {}
void foo(int a, int b) {}

int main()
{
	// 동일 이름의 함수가 여러개 있을때.. 직접 호출은 문제 없습니다.
	foo();
	foo(1);
	foo(1, 2);

//	chronometry(&foo, 1); // error
//	printf("%p\n", &foo); // error

	chronometry(static_cast<void(*)(int)>(&foo), 1); //  ok

}









