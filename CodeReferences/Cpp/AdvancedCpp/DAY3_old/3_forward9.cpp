
template<typename T> class Test
{
public:
	// �Ʒ� �ڵ�� ���� forwarding reference�� �ƴմϴ�.
	// �Ʒ� �Լ��� ���ø��� �ƴϰ�, Ŭ���� ���ø��� �Ϲ� ��� �Լ� �Դϴ�.
	void foo(T&& arg) {}

	// forwarding reference�� �Ƿ��� "�Լ� ��ü�� ���ø�" �̾�� �մϴ�
	template<typename U> void goo(U&& arg) {}
};
int main()
{
	int n = 0;
	Test<int> t; // �̶� T�� �̹� int�� �����˴ϴ�.
				 // void foo(int&&) �� ������.

	// ������ ������ ��� ������
	t.foo(n); // error
	t.foo(10);// ok
	t.goo(n); // ok
	t.goo(10); //ok 
}