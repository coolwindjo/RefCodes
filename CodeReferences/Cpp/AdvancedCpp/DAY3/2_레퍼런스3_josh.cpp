using LREF = int&; // typedef int& LREF;
using RREF = int&&;

int main()
{
	int n = 10;

	LREF r1 = n;
	RREF r2 = 10;

	// ----------------------------------------
	// Reference collapsing 현상
	// 규칙: 양쪽이 모두 &&일때면 && 로 결정
	LREF& r3 = n;	// int& 	&	=> int&
	RREF& r4 = n;	// int&&	&	=> int&

	LREF&& r5 = n;	// int&		&&	=> int&
	RREF&& r6 = 10;	// int&&	&&	=> int&&
	// ----------------------------------------

	int& && r7 = n;	// Error: 직접 Reference를 2번 표기 할 수 없다.

	// Reference collapsing이 적용되는 표현식
	// 1. typedef(using)
	// 2. template
	// 3. decltype
	int x[3] = {1,2,3};
	decltype(x[0])&& r; 	// int& && r => int& r;	초기화가 안돼서 Error

	foo<int&>(n);

}
template<typename T> void foo(T&& n) // foo( int& && n ) => foo(int& n)