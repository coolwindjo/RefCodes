#include <iostream>


void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

template<typename F> void chronometry(F f, int& arg)
{
	f(arg);
}

// main						chronometry								hoo(int&&)
// hoo(10) =============================================================> ok
// chrometry(hoo, 10) =====> int&& arg = 10;
//							 f(arg) ===============> hoo(int&) �� ã�´�.. error
//                          f( static_cast<int&&>(arg) ) ===============> ok

template<typename F> void chronometry(F f, int&& arg)
{
	// int&& arg = 10  ���� �޾Ҵµ�.. arg�� �̸��� �����Ƿ� lvalue �̴�.
	//f(arg);	// hoo(int&) �� ã�� �ȴ�.

	// ���ڸ� �����Ҷ� �ٽ� rvalue�� ĳ�����ؼ� �����Ѵ�.
	f( static_cast<int&&>(arg) );
}

int main()
{
	hoo(10); // ok
	chronometry(hoo, 10); // �� �ڵ尡 �ǹǷ�.. �� �͵� �翬�� �Ǿ�� �մϴ�.
}
