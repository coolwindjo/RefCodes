#include <iostream>

template<typename T> void foo(T a)
{
	// 아래 코드는 컴파일 에러가 있을까요 ?
	// if : 실행시간 조건만.. 컴파일 시간에 false 인지 알아도..
	//		"템플릿 코드" => "c++코드로 생성"
//	if ( false )
//		*a = 10;

	// C++17의 새로운 if 문 - 컴파일 시간 if 문
	// 조건이 false 라면 "템플릿 코드" => "C++코드로 생성" 안됨.
	// /std:c++latest ,  -std=c++17  옵션 필요..
	int b = 0;
	if constexpr (false)
		//*b = 10;  // 이 코드는 템플릿 자체를 검증할때.. 조사.. 무조건 에러
		*a = 10;	// 이 코드는 템플릿 자체를 검증할때는 에러여부 알수없고
				    // C++ 코드가 생성된후.. 다시 컴파일...
}

template<typename T> void goo(T a)
{
	// 아래 코드에서 에러를 생각해 보세요.
//	hoo();  // hoo 함수는 없다... error
	hoo(a); // a의 타입이 결정되어야만 에러인지 아닌지 알수 없다.

//int b = 10;
//	*b = 0; // a와 관련없이 무조건 에러.

//	*a = 10;
}


int main()
{
	int n = 0;

//	foo(&n); // ok
	foo(n);
}