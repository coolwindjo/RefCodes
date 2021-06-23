
int main()
{
	int n = 10;

	// 규칙 1. non const lvalue reference 는 lvalue 만 가리킬수 있다.
	int& r1 = n;	// ok
	int& r2 = 10;	// error

	// 규칙 2. const lvalue reference 는 lvalue 와 rvalue를 모두 가리킬수 있다.
	const int& r3 = n;	// ok
	const int& r4 = 10;	// ok.. "temporary materization"

	// 규칙 3. C++11 에서는 상수성이 없이 rvalue를 가리킬 필요가 있었다.
	//		move와 완벽한 전달 때문에..
	//		rvalue reference는 rvalue 만 가리킬수 있다.
	int&& r5 = n;  // error
	int&& r6 = 10; // ok.. 

	// 참고. const rvalue reference
	const int&& r7 = n;  // error.
	const int&& r8 = 10; // ok

}