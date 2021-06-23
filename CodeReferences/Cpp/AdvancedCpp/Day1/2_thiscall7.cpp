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

	/*/
	template<typename T, typename R, typename ...ARGS>
	ostream& operator<<( R (T::*f)(ARGS...) )
	{
		printf("%p", f);
		return *this;
	}
	//*/
};
ostream cout;

int main()
{
	int n = 0;
	double d = 0;

	cout << n << "\n";				// cout.operator int()
	cout << d << "\n";		
	cout << &d << "\n";				// cout.operator void*()
	cout << &main << "\n";			// cout.operator void*()	??????????
	cout << &Dialog::foo << "\n";	// Member Function Pointer는 void*에 담을 수 없다.
									// size 가 4보다 클 수 있기 때문 (this_offset...)
	if (&Dialog::foo) {
									// BUT, bool 로 전환될 수 는 있다.
									// Member Function Pointer => bool 변환시, 1 로 변경됨
		cout << "\n";
	}
	printf("%p\n", &Dialog::foo);	// if you want to print the address...
	// Member function address 확인 할 때는 cout 은 쓰지 말자
}


