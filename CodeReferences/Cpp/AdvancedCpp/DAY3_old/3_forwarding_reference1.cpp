// 함수 인자로!
// int&  : int 형의 lvalue 만 전달할수 있다.
// int&& : int 형의 rvalue 만 전달할수 있다.

// T& : 임의 타입의 lvalue 만 전달할수 있다.

// T&& : 임의 타입의 lvalue 와 rvalue 를 모두 받을수 있다.

//		"받을수 있다" 는 의미는 lvalue를 받는 함수를 생성..
//								rvalue를 받는 함수를 생성..
//								=> 생성된 모든 함수는 "참조 버전"이 핵심!
// rvalue(10)을 보내면 ==> T : int,    최종 함수 f4(int&&)
// lvalue(n)을 보내면  ==> T : int&,   최종 함수 f4(int&)

// "universal reference" 라고 부르자고 "effective modern C++" 저자가 제안했지만
// "forwarding referfence" 라고 부르기로 결정





void f1(int&  r) {}
void f2(int&& r) {}




template<typename T> void f3(T& a)
{
}

int main()
{
	int n = 10;

	// 1. 사용자가 타입을 명시적으로 전달하는 경우
	f3<int>(n);	   // T : int    T& : int&    최종함수 모양 : void f3(int& a)
	f3<int&>(n);   // T : int&   T& : int& &  최종함수 모양 : void f3(int& a)
	f3<int&&>(n);  // T : int&&  T& : int&& & 최종함수 모양 : void f3(int& a)

	// 2. 사용자가 타입을 전달하지 않으면
	//	  컴파일러는 인자를 보고 "최대한 노력해서 함수를 생성 하려고 합니다"
	f3(10); // 타입 T를 결정할수없다. 컴파일 에러!
	f3(n);  // T 는 int로 결정.
}














template<typename T> void f4(T&& a)
{
}

int main()
{
	int n = 10;

	// 1. 사용자가 타입을 전달할때
	f4<int>(10);    // T : int	   T&& : int&&			최종 함수 : f4(int&& a)
	f4<int&>(n);	// T : int&	   T&& : int& &&		최종 함수 : f4(int& a)
	f4<int&&>(10);  // T : int&&   T&& : int&& &&		최종 함수 : f4(int&& a)

	// 2. 사용자가 타입을 전달하지 않으면
	//	  인자를 보고 함수를 생성할수 있도록 T를 결정
	f4(n);	// T : int& 로 결정,   최종 함수는 f4(int&)
	f4(10); // T : int  로 결정,   최종 함수는 f4(int&&)
}












