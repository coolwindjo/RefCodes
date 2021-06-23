
template<typename T> class Test
{
public:
	// 아래 코드는 절대 forwarding reference가 아닙니다.
	// 아래 함수는 템플릿이 아니고, 클래스 템플릿의 일반 멤버 함수 입니다.
	void foo(T&& arg) {}

	// forwarding reference가 되려면 "함수 자체가 템플릿" 이어야 합니다
	template<typename U> void goo(U&& arg) {}
};
int main()
{
	int n = 0;
	Test<int> t; // 이때 T는 이미 int로 결정됩니다.
				 // void foo(int&&) 로 결정됨.

	// 다음중 에러를 모두 고르세요
	t.foo(n); // error
	t.foo(10);// ok
	t.goo(n); // ok
	t.goo(10); //ok 
}