using LREF = int&; // typedef int& LREF;
using RREF = int&&;

int main()
{
	int n = 10;

	LREF r1 = n;
	RREF r2 = 10;
	//-----------------------
	// reference collapsing ���� 
	// ��Ģ : ������ ��� && �϶��� && �� ����
	LREF& r3 = n; // int&  &	=> int&
	RREF& r4 = n; // int&& &	=> int&
	LREF&& r5 = n; // int&  &&	=> int&
	RREF&& r6 = 10;// int&& &&	=> int&&
	//------------------------------------------

	int& && r7 = n; // error.. ���� ���۷����� 2�� ǥ���Ҽ� ����.

	// reference collapsing�� ����Ǵ� ǥ����
	// 1. typedef(using)
	// 2. template
	// 3. decltype 
	// ���� ��츸 ����
	int x[3] = { 1,2,3 };
	decltype(x[0])&& r;   // int& && r  => int& r;

	foo<int&>(n);
}
template<typename T> void foo(T&& n) // foo( int& && n)  => foo(int& n)
{
}






