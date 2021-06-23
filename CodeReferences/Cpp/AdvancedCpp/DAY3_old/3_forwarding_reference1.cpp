// �Լ� ���ڷ�!
// int&  : int ���� lvalue �� �����Ҽ� �ִ�.
// int&& : int ���� rvalue �� �����Ҽ� �ִ�.

// T& : ���� Ÿ���� lvalue �� �����Ҽ� �ִ�.

// T&& : ���� Ÿ���� lvalue �� rvalue �� ��� ������ �ִ�.

//		"������ �ִ�" �� �ǹ̴� lvalue�� �޴� �Լ��� ����..
//								rvalue�� �޴� �Լ��� ����..
//								=> ������ ��� �Լ��� "���� ����"�� �ٽ�!
// rvalue(10)�� ������ ==> T : int,    ���� �Լ� f4(int&&)
// lvalue(n)�� ������  ==> T : int&,   ���� �Լ� f4(int&)

// "universal reference" ��� �θ��ڰ� "effective modern C++" ���ڰ� ����������
// "forwarding referfence" ��� �θ���� ����





void f1(int&  r) {}
void f2(int&& r) {}




template<typename T> void f3(T& a)
{
}

int main()
{
	int n = 10;

	// 1. ����ڰ� Ÿ���� ��������� �����ϴ� ���
	f3<int>(n);	   // T : int    T& : int&    �����Լ� ��� : void f3(int& a)
	f3<int&>(n);   // T : int&   T& : int& &  �����Լ� ��� : void f3(int& a)
	f3<int&&>(n);  // T : int&&  T& : int&& & �����Լ� ��� : void f3(int& a)

	// 2. ����ڰ� Ÿ���� �������� ������
	//	  �����Ϸ��� ���ڸ� ���� "�ִ��� ����ؼ� �Լ��� ���� �Ϸ��� �մϴ�"
	f3(10); // Ÿ�� T�� �����Ҽ�����. ������ ����!
	f3(n);  // T �� int�� ����.
}














template<typename T> void f4(T&& a)
{
}

int main()
{
	int n = 10;

	// 1. ����ڰ� Ÿ���� �����Ҷ�
	f4<int>(10);    // T : int	   T&& : int&&			���� �Լ� : f4(int&& a)
	f4<int&>(n);	// T : int&	   T&& : int& &&		���� �Լ� : f4(int& a)
	f4<int&&>(10);  // T : int&&   T&& : int&& &&		���� �Լ� : f4(int&& a)

	// 2. ����ڰ� Ÿ���� �������� ������
	//	  ���ڸ� ���� �Լ��� �����Ҽ� �ֵ��� T�� ����
	f4(n);	// T : int& �� ����,   ���� �Լ��� f4(int&)
	f4(10); // T : int  �� ����,   ���� �Լ��� f4(int&&)
}












