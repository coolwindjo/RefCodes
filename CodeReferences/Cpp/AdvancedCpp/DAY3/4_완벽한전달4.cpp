#include <iostream>


void foo(int a) {}
void goo(int& a) { a = 100; }
void hoo(int&& a) {}

// "T&&" �� ����ϸ� �Ʒ� 2���� �Լ��� �ڵ� �����Ҽ� �ִ�.
// �׷���,, ������ 2�� �Լ��� ������ ���ƾ� �Ѵ�.

/*
template<typename F> void chronometry(F f, int& arg)
{
	//f(arg);
	f( static_cast<int&>(arg) ); // �ʿ� ���� ĳ���� ������...
								// �־ ���� ���� �ʽ��ϴ�.
}
template<typename F> void chronometry(F f, int&& arg)
{
	f(static_cast<int&&>(arg));
}
*/

// �Ʒ� �Լ��� �ᱹ �� 2���� �Լ��� �ڵ� �����մϴ�.
template<typename F, typename T> void chronometry(F f, T&& arg)
{
	// �Ʒ� ĳ������ 
	// "lvalue(�� ���ڷ� ����)�� lvalue �� ĳ�����ϰ�"
	// "rvalue(�� ���ڷ� ����)�� rvalue �� ĳ�����Ѵ�."
	// f(static_cast<T&&>(arg));

	f( std::forward<T>(arg) ); // std::forward �Լ��� ��ó�� ĳ�����ϴ� ��Ȱ�� �մϴ�.
							   // �ٸ� ���� ���ڸ� �����Ҷ� ����Ѵٴ� �ǹ̷�
							   // "forward" ��� �ܾ� ���
}

// ���!!! �Ϻ��� ������ �Ϸ���
// 1. ���ڸ� T&& �� ��������
// 2. ���ڸ� �ٸ����� ����°�� std::forward<T>(arg) �� ��� ��������..


int main()
{
	int n = 10;
	chronometry(foo, 10); // T : int,   T&& : int&&   ĳ���� : static_cast<int&&>(arg)
	chronometry(goo, n);  // T : int&   T&& : int& && ĳ���� : static_cast<int&>(arg)
}
