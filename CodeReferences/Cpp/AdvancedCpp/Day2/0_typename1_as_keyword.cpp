class Test
{
public:
	enum { value = 1 };
	typedef int DWORD;
};
int p = 0;

// 핵심 1. Template 에 의존해서 Type을 꺼낼때에는 반드시 typename을 적어야 한다.
// typename T::DWORD * p;
template<typename T>
void foo(T a)
{
	// 아래 2줄에서 * 의 의미를 생각해 보세요(1. 곱하기, 2. 포인터 변수 선언)
	// ClassName::"Name"	=> "Name" can be a value or a type
	/*/
	Test::value * p;	// 1. 
	Test::DWORD * p;	// 2.
	/*/
	// 아래 Code 를 해석해보자
	// T::"Name" 			=> "Name" is a value
	// typename T::"Name"	=> "Name" is a type
	T::value * p;	// OK
#if 0
	T::DWORD * p;	// error 
#else
	typename T::DWORD * p;	// OK
#endif
	//*/
}
int main()
{
	Test t;
	foo(t);
}