int main()
{
	int n = 10;

	// 다음중 에러를 모두 고르세요
	auto a1 = n;	// ok
	auto a2 = 10;	// ok

	auto& a3 = n;	// ok
	auto& a4 = 10;	// error

	// 핵심 . auto 는 항상 T와 유사합니다.
	// auto&& 는 결국 T&& 의 의미 입니다
	// T&&  arg = 함수 인자;
	// auto&& a = 우변
	auto&& a5 = n;	// auto : int&    auto&& : int& &&    int& a5 = n;
	auto&& a6 = 10; // auto : int     auto&& : int&&      int&& a6 = 10;

	// 핵심 : auto&& 는 "forwarding reference" 입니다.

//	auto a5 = n; // 이렇게 하면 int a5 = n;
}

//template<typename T> void foo(T&& arg) {}
//foo(n); // T : int&