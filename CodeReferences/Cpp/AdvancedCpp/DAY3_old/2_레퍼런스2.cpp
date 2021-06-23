#include <iostream>

void foo(int& a)       { std::cout << "int&"       << std::endl; }
void foo(const int& a) { std::cout << "const int&" << std::endl; }
void foo(int&& a)      { std::cout << "int&&"      << std::endl; }

int main()
{
	int n = 10;

	foo(n);	// 1번 호출, 1번이 없으면 2번 호출
	foo(10);// 3번 호출, 없으면 2번.. 

	int& r1 = n;
	foo(r1);	// 1번 호출, 없으면 2번 호출

	int&& r2 = 10;  // 10은 이름이 없다 - rvalue
					// r2는 이름이 있다 - lvalue 이다.
	// 타입과 value 속성을 헷갈리지 마세요
	
	//			타입			value 속성
	// 10		int				rvalue
	// r2		int&&			lvalue
	// void foo(int&&) : int&& 타입을 받겠다는게 아니라!!!
	//					rvalue 표현식을 인자로 받겠다는 의미.

	foo(r2);	// 1번

	// r2를 3번으로 보내려면 r2를 (1) 타입을 변경해야 한다.
	//							  (2) value 속성을 변경해야 한다. => 답!!!
	foo( static_cast<int&&>(r2) ); // 이 코드는 타입 캐스팅이 아닌 
								// value casting 입니다.
								// cppreference.com 에서 static_cast 검색해보세요
						// lvalue(glvalue) => rvalue(정확히는 xvalue)로 캐스팅
}







