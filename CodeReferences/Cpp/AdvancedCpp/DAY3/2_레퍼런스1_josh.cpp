int main()
{
	int n = 10;

	// 규칙 1. non const LVALUE reference 는 lvalue만 가리킬 수 있다.
	int& r1 = n;  	// OK.
	int& r2 = 10; 	// Error

	// 규칙 2. const LVALUE reference는 lvalue와 rvalue 모두 가리킬 수 있다.
	const int& r1 = n; 	// OK
	const int& r2 = 10; // OK: "Temporary materization"

	// 규칙 3. C++11에서는 상수성이 없이 rvalue를 가리킬 필요가 있었다.
	// 		move와 완벽한 전달 때문에...
	// 		rvalue reference는 rvalue만 가리킬 수 있다.
	int&& r5 = n; // Error
	int&& r6 = 10; // OK
}