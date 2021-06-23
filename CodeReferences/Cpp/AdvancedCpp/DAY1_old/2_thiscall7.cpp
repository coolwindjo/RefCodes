#include <iostream>

class Dialog
{
public:
	void foo() {}
};

class ostream
{
public:
	ostream& operator<<(const char* a) { printf("%s", a); return *this; }
	ostream& operator<<(void*	 a)    { printf("void*  : %p", a); return *this; }
	ostream& operator<<(int		 a)    { printf("int    : %d", a); return *this; }
	ostream& operator<<(double   a)    { printf("double : %f", a); return *this; }
	ostream& operator<<(bool     a)    { printf("bool   : %d", a); return *this; }

	template<typename T, typename R, typename ... ARGS>
	ostream& operator<<( R (T::*f)(ARGS...) )
	{
		printf("%p", f);
		return *this;
	}
};
ostream cout;

int main()
{
	int n = 0;
	double d = 0;
	cout << n << "\n"; // cout.operator int()
	cout << d << "\n";;
	cout << &d << "\n";	   // cout.operator void*()
	cout << &main << "\n"; // cout.operator void*()

	cout << &Dialog::foo << "\n"; // 멤버 함수 포인터는 void* 에 담을수 없다.
								  // 하지만 bool로 변환될수 있다.
								  // 하지만, 함수주소 => bool값(즉, 1)로 변경되어서 전달
	printf("%p\n", &Dialog::foo);

	//if ( 멤버함수포인터 ) // ok
}

// 오전 소스는 cafe.naver.com/cppmaster 에 올려 놓았습니다.

