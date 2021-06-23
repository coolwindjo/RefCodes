#include <iostream>

void foo(int& a)       { std::cout << "int&" << std::endl; }
void foo(const int& a) { std::cout << "const int&" << std::endl; }
void foo(int&& a)      { std::cout << "int&&" << std::endl; }

int main()
{
	int n = 10;

	foo(n);		// 1번 호출, 1번이 없으면 2번 호출 (const가 없어서...)
	foo(10);	// 3번 호출, 없으면 2번 호출

	int& r1 = n;
	foo(r1);	// 1번 호출, 없으면 2번 호출

	int&& r2 = 10;	// 10은 이름이 없다. - rvalue
					// r2는 이름이 있다. = lvalue

	// Type과 value 속성을 헷갈리지 마세요
	// 		Type		value 속성
	//10	int			rvalue
	//r2	int&&		lvalue

	// void foo(int&&)	// int&& Type을 받겠다는 게 아니라, 
						// rvalue 표현식만 인자로 받겠다는 의미
	foo(r2);	// 1번 호출, 1번이 없으면 2번 호출 (const가 없어서...)

	// r2를 3번으로 보내려면 r2를 (1) Type을 변경해야 한다.
	//							(2) value 속성을 변경해야 한다. => 정답!
	foo(static_cast<int&&>(r2))	// 이 Code는 Type Casting이 아닌
								// value casting 입니다.
								// cppreference.com 에서 static_cast 검색 => 3) if new type is an rvalue ...
								// lvalue(glvalue) => rvalue(정확히는 xvalue)로 Casting

}







