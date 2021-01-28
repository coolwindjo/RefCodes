// 9_완벽한전달_주의사항
#include <iostream>

template<typename F, typename T>
void chronometry(F f, T&& arg)
{
	f(std::forward<T>(arg));
}

void foo(int* p) {}

int main()
{
	int n = 0;
	foo(0); // ok.     literal 0은 포인터로 암시적 변환 되지만
	foo(n); // error   int 는 포인터로 변환 될수 없다.

//	chronometry(foo, 0); // error.

	chronometry(foo, nullptr); // ok...

	// nullptr의 타입은 "nullptr_t" 타입입니다.
	nullptr_t arg = nullptr;

	// nullptr_t 타입은 모든 포인터 타입으로 암시적 변환 됩니다.
	int* p = arg; // ok

}













