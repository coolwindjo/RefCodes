// cafe.naver.com/cppmaster 에서 
// 2일차 사전소스를 받으시면 됩니다.

// 핵심 : 템플릿에 의존해서 타입을 꺼낼때는 반드시 typename 을 적어야 한다.
//  typename T::DWORD * p;

class Test
{
public:
	enum { value = 1 };
	typedef int DWORD;
};
int p = 0;

template<typename T> void foo(T a)
{
	// 아래 2줄에서 * 의 의미를 생각해 보세요(1. 곱하기, 2. 포인터 변수 선언)
	// 클래스이름::"이름"   => 값 또는 타입
	//Test::value * p; // 곱하기의 의미.
	//Test::DWORD * p; // 포인터 변수 선언

	// 아래 코드 해석해 보세요
	// T::이름          => 값으로 해석.
	// typename T::이름 => 값이 아닌 이름으로 해석해 달라.
	T::value * p; // ok..
//	T::DWORD * p; // error.
	typename T::DWORD * p; // ok.

	
}

int main()
{
	Test t;
	foo(t);
}

