int x = 10;

int& foo(int a, int b) { return x; }

int main()
{
	auto ret1 = foo(10, 20);
				// int& 이지만 auto는 참조를 제거하고 타입 결정
				// int ret1 = foo(10, 20);

	// decltype(함수호출식) : 함수 호출의 결과로 나오는 타입 조사(반환타입)
	//						실제 함수가 호출되는 것은 아님.
	decltype( foo(10, 20) ) ret2 = foo(10, 20);
				// int& ret2 = foo(10, 20);    의 의미..

	// C++14 에서 나온 새로운 기술
	// 우변의 표현식을 auto 자리에 넣어 달라.
	// 결국 "우변으로 타입추론" 단, auto 추론이 아닌 decltype 추론 기술 사용.
	decltype(auto) ret3 = foo(10, 20);
			// int& ret3 = foo(10, 20); 

	auto&& ret4 = foo(10, 20); // 우변이 참조리턴이면(lvalue)이므로 
							// int& ret4 = foo(10,20);
							// 값리턴 이면.. rvalue 이므로
							// int ret4 = foo(10,20);
}