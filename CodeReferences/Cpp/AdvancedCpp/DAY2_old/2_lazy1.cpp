// �Ʒ� �ڵ�� �� �����ϱ�� ?
/*
class A
{
	int data;
public:
	void foo() { *data = 10; } 
};

int main()
{
	A a;
}
*/

// �ٽ� : Ŭ���� ���ø��� �ִ� ��� �Լ���.. ����� �Լ��� ���� C++ �ڵ�� �����˴ϴ�.
//        "������ �ν��Ͻ�ȭ"��� ����..
template<typename T> class A
{
	T data;
public:
	void foo() { *data = 10; }
};

int main()
{
	A<int> a;

	a.foo();
}








