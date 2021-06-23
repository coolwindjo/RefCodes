
int main()
{
	int n = 10;

	// ��Ģ 1. non const lvalue reference �� lvalue �� ����ų�� �ִ�.
	int& r1 = n;	// ok
	int& r2 = 10;	// error

	// ��Ģ 2. const lvalue reference �� lvalue �� rvalue�� ��� ����ų�� �ִ�.
	const int& r3 = n;	// ok
	const int& r4 = 10;	// ok.. "temporary materization"

	// ��Ģ 3. C++11 ������ ������� ���� rvalue�� ����ų �ʿ䰡 �־���.
	//		move�� �Ϻ��� ���� ������..
	//		rvalue reference�� rvalue �� ����ų�� �ִ�.
	int&& r5 = n;  // error
	int&& r6 = 10; // ok.. 

	// ����. const rvalue reference
	const int&& r7 = n;  // error.
	const int&& r8 = 10; // ok

}