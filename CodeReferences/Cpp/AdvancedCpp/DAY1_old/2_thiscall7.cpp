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

	cout << &Dialog::foo << "\n"; // ��� �Լ� �����ʹ� void* �� ������ ����.
								  // ������ bool�� ��ȯ�ɼ� �ִ�.
								  // ������, �Լ��ּ� => bool��(��, 1)�� ����Ǿ ����
	printf("%p\n", &Dialog::foo);

	//if ( ����Լ������� ) // ok
}

// ���� �ҽ��� cafe.naver.com/cppmaster �� �÷� ���ҽ��ϴ�.

