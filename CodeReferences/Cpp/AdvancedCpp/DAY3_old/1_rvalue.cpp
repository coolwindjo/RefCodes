int x = 10;
int foo()  { return x; } // x�� ��(10)�� ����
int& goo() { return x; } // x�� �޸� ���� ��ȯ..

// lvalue : ��ȣ�� ���ʿ� �ü� �ִ�.(lvalue �� rvalue �� �Ͻ��� ��ȯ�ȴ�.)
//			���� �̸��� �ְ�
//			���� ������ ������� ����Ҽ� �ִ�.
//			�ּ� �����ڷ� �ּҸ� ���Ҽ� �ִ�.
//			������ ��ȯ�ϴ� �Լ�

// rvalue : ��ȣ�� �����ʿ��� �ü� �ִ°�.
//			���� �ְ�, �̸��� ����.
//			���� ���忡���� ��밡��.	
//			�ּ� �����ڷ� �ּҸ� ���Ҽ� ����.
//			���� ��ȯ�ϴ� �Լ� 
//			�ӽð�ü, ���ͷ�(10, 3.4)
int main()
{
	int v1 = 10, v2 = 10;  // mov v2�ּ�, 10
	
	v1 = 20;	// v1 : lvalue    20 : rvalue 
	10 = v1;
	v2 = v1;

	int* p1 = &v1;
	int* p2 = &10; 

	foo() = 20; // error.. 10 = 20
	goo() = 20; // ok..

	const int c = 10;
	c = 20;				// c�� rvalue �ϱ�� ? lvalue �ϱ�� ?
						// c �� immutable lvalue �Դϴ�.

	// ��� rvalue �� ����̴�.?? = �ƴϴ�.!!!
	//							������ ���ʿ� �ü� ����..!
	Point(1, 2).x = 10;// error
	Point(1, 2).set(1, 2); //ok
}








